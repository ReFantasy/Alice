#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "interface.h"
#include <QCloseEvent>
#include <QDebug>
#include <QGraphicsOpacityEffect>

#ifdef __APPLE__
#include "global_clipboard_message_for_mac.h"
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // qDebug() << QSqlDatabase::drivers();

    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    QStatusBar *statusbar = new QStatusBar(this);
    statusbar->hide();
    this->setStatusBar(statusbar);
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    ui->textEdit->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.75);

    InitSystemTray();

    clipboard = QApplication::clipboard();

    settings = new QSettings(this);
    settings->setValue("from", "auto");
    settings->setValue("to", "zh");

    // create an default translation engine
    auto engine = std::make_shared<BaiduEngine>();
    engine->SetIdKey("20210330000753038", "l5ddAZlgKFfkd6sgR_Oy");
    engine_interface = new EngineInterface();
    engine_interface->SetTranslateEngine(engine);
    connect(engine_interface, &EngineInterface::TranslateFinished, this, &MainWindow::ReceiveTranslatedResult);

    // 剪切板内容变化时自动将文本传递给翻译引擎
    connect(clipboard, &QClipboard::dataChanged, this, [this]() {
        QString clip_str = clipboard->text().toUtf8();
        // 空格替换换行符 QRegularExpression
        QString replaced_str = clip_str.replace(QRegularExpression(QString("\\n")), QChar(32));
        replaced_str = replaced_str.replace(QRegularExpression(QString("\\r")), QChar(32));
        engine_interface->Translate(settings->value("from").toString(), settings->value("to").toString(), replaced_str);
    });

#ifdef __APPLE__
    SetQtClipboard(clipboard);
#endif

    // 文本显示控件样式设置
    ui->textEdit->setStyleSheet(QString::fromUtf8("border:1px solid green;background-color: rgb(250, 250, 250)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (systemTray->isVisible())
    {
        this->hide();
        event->ignore();
    }
    else
    {
        // event->accept();
        QMainWindow::closeEvent(event);
    }
}

void MainWindow::ReceiveTranslatedResult(QString trans_result)
{
    ui->textEdit->setText(trans_result);
    // qDebug() << trans_result;
}

void MainWindow::InitSystemTray()
{
    systemTray = new QSystemTrayIcon(this);
    systemTray->setToolTip("Alice Translation");
    systemTray->setIcon(QIcon(":/resource/logo.png"));
    systemTray->setVisible(true);

    // Tray Menu
    QMenu *tray_menu = new QMenu();

    // preference
    preference = new Preference(nullptr, settings);
    auto preference_action = new QAction(tray_menu);
    preference_action->setText("Preference");
    tray_menu->addAction(preference_action);
    connect(preference_action, &QAction::triggered, this, [this]() {
        qDebug() << "click";
        this->preference->show();
    });

    tray_menu->addSeparator();

    // close app
    auto close_app_action = new QAction(tray_menu);
    close_app_action->setText("Quit");
    tray_menu->addAction(close_app_action);
    connect(close_app_action, &QAction::triggered, this, [this] {
        this->systemTray->hide();
        exit(0);
    });

    systemTray->setContextMenu(tray_menu);
    connect(systemTray, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        switch (reason)
        {
        case QSystemTrayIcon::Unknown: // 未知请求
            break;
        case QSystemTrayIcon::Context: // 请求托盘菜单

            break;
        case QSystemTrayIcon::Trigger: // 单击托盘
            // this->showNormal();
            break;
        case QSystemTrayIcon::DoubleClick: // 双击托盘
            this->showNormal();
            break;
        }
    });
    systemTray->show();
}
