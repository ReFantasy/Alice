#include "mainwindow.h"
#include "QProcess"
#include "QStatusBar"
#include "translate_engine/interface.h"
#include <QGraphicsOpacityEffect>
#include <qprocess.h>
#include "QVBoxLayout"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // new all variable
    engine_interface = new EngineInterface(this);
    settings = new QSettings(this);
    textEdit = new QTextEdit(this);

    auto layout = new QVBoxLayout(this);
    layout->setDirection(QBoxLayout::BottomToTop);
    layout->addWidget(textEdit);
    /*this->setLayout(layout);*/
    this->centralWidget()
    

    /*ui->setupUi(this);*/

    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    this->statusBar()->hide();
    this->resize(600, 500);

    settings->setValue("from", "auto");
    settings->setValue("to", "zh");

    auto engine = std::make_shared<BaiduEngine>();
    engine->SetIdKey("20210330000753038", "l5ddAZlgKFfkd6sgR_Oy");

    // create translation interface
    engine_interface->SetTranslateEngine(engine);
    connect(engine_interface, &EngineInterface::TranslateFinished, this, &MainWindow::ShowTranslatedResult);

    // 剪切板内容变化时自动将文本传递给翻译引擎
    static auto clipboard = QApplication::clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, [this]() {
        QString clip_str = clipboard->text().toUtf8();
        if (clip_str.isEmpty())
            return;
        // 空格替换换行符 QRegularExpression
        QString replaced_str = clip_str.replace(QRegularExpression(QString("\\n")), QChar(32));
        replaced_str = replaced_str.replace(QRegularExpression(QString("\\r")), QChar(32));
        engine_interface->Translate(settings->value("from").toString(), settings->value("to").toString(), replaced_str);
    });

    connect(clipboard, &QClipboard::selectionChanged, this, [this]() {
        QString clip_str = clipboard->text(QClipboard::Selection).toUtf8();
        if (clip_str.isEmpty())
            return;
        QString replaced_str = clip_str.replace(QRegularExpression(QString("\\n")), QChar(32));
        replaced_str = replaced_str.replace(QRegularExpression(QString("\\r")), QChar(32));
        engine_interface->Translate(settings->value("from").toString(), settings->value("to").toString(), replaced_str);
    });
}

void MainWindow::ShowTranslatedResult(QString trans_result)
{
    this->textEdit->setText(trans_result);
}
