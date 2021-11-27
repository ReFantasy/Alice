#include <QNetworkAccessManager>
#include <QClipboard>
#include <QSettings>
#include <QDebug>
#include <QMenu>
#include <QCloseEvent>
#include "widget.h"
#include "ui_widget.h"

#include "translation.h"
#include "httprequest.h"
#include "preference.h"
#include <QDialog>
#include <QScreen>
#include <QRegularExpression>

const unsigned int preference_widget_posx = 200;
const unsigned int preference_widget_posy = 200;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Alice");
    setWindowFlag(Qt::WindowStaysOnTopHint,true);

//    QScreen *screen=QGuiApplication::primaryScreen();
//    int screen_width = screen->availableGeometry().width();
//    this->resize(screen_width*0.25,screen_width*0.25*0.75);


    clipboard = QApplication::clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, &Widget::ClipDataChanged);


    settings = new QSettings(QCoreApplication::applicationDirPath()+QString("/Alice.ini"),
                             QSettings::IniFormat);
    InitConfig();


    // set translation engine
    http_request = new HttpRequest(this);
    connect(http_request, &HttpRequest::TranslateFinished, this, &Widget::ReceiveTranslatedResult);
    std::shared_ptr<TranslateEngine> _tranlation_engine;
    auto engine = std::make_shared<BaiduEngine>();
    engine->SetIdKey(settings->value("appid").toString(), settings->value("key").toString());
    http_request->SetTranslateEngine(engine);

    // SystemTray Setting
    systemTray = new QSystemTrayIcon(this);
    systemTray->setToolTip("Alice Translation");
    systemTray->setIcon(QIcon(":/images/Images/logo.png"));
    systemTray->setVisible(true);

    // Tray Menu
    QMenu* tray_menu = new QMenu();

    //preference
    auto preference_action = new QAction(tray_menu);
    preference_action->setText("Preference");
    tray_menu->addAction(preference_action);
    connect(preference_action, &QAction::triggered, this, &Widget::SetPreference);
    tray_menu->addSeparator();
    // close app
    auto close_app_action = new QAction(tray_menu);
    close_app_action->setText("Quit");
    tray_menu->addAction(close_app_action);
    connect(close_app_action, &QAction::triggered, this, &Widget::CloseApp);

    systemTray->setContextMenu(tray_menu);

    // Connect Tray signals
    connect(systemTray, &QSystemTrayIcon::activated, this, &Widget::OnSystemTrayClicked);//点击托盘，执行相应的动作
    systemTray->show();

    // Create Preference Dialog
    preference = new Preference(nullptr, settings);
    //preference->Settings(this->settings);

    // 文本显示控件样式设置
    ui->textEdit->setStyleSheet(QString::fromUtf8("border:1px solid green;background-color: rgb(250, 250, 250)"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(systemTray->isVisible())
    {
        // 隐藏主界面并忽略窗口关闭信号
        this->hide();
        event->ignore();
    }
    else
    {
        Widget::closeEvent(event);
    }

}

void Widget::ReceiveTranslatedResult(QString trans_result)
{
    ui->textEdit->setText(trans_result);
}

void Widget::ClipDataChanged()
{
    QString clip_str = clipboard->text().toUtf8();

    // 空格替换换行符 QRegularExpression
    QString replaced_str = clip_str.replace(QRegularExpression(QString("\\n")), QChar(32));

    http_request->Translate(settings->value("from").toString(), settings->value("to").toString(), replaced_str);
}

void Widget::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Unknown: // 未知请求
        break;
    case QSystemTrayIcon::Context: // 请求托盘菜单

        break;
    case QSystemTrayIcon::Trigger: // 单击托盘
        this->showNormal();
        break;
    case QSystemTrayIcon::DoubleClick://双击托盘
        this->showNormal();
        break;
    }

}

void Widget::InitConfig()
{
    if(settings->value("appid").isNull())
    {
        settings->setValue("appid", "your_appid");
    }
    if(settings->value("key").isNull())
    {
        settings->setValue("key", "your_key");
    }
    qDebug()<<settings->value("appid").toString();

    if(settings->value("from").isNull())
    {
        settings->setValue("from", "auto");
    }
    if(settings->value("to").isNull())
    {
        settings->setValue("to", "zh");
    }
    settings->sync();
}

void Widget::CloseApp()
{
    systemTray->hide();
    exit(0);
}



void Widget::SetPreference()
{
    preference->move(preference_widget_posx,preference_widget_posy);
    preference->show();
}

