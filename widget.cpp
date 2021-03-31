#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtNetwork>
#include <QUrl>
#include <QString>
#include <QJsonDocument>
#include <QClipboard>
#include "querycode.h"
#include "httprequest.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Alice");
    setWindowFlag(Qt::WindowStaysOnTopHint,true);

    hr = new HttpRequest(this);
    connect(hr, &HttpRequest::QueryDst, this, &Widget::QueryDst);

    clipboard = QApplication::clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, &Widget::ClipDataChanged);


    settings = new QSettings(QCoreApplication::applicationDirPath()+QString("/Alice.ini"),
                             QSettings::IniFormat);
    if(settings->value("appid").isNull())
    {
        settings->setValue("appid", "your_appid");
    }
    if(settings->value("key").isNull())
    {
        settings->setValue("key", "your_key");
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::QueryDst(QString dst)
{
    //ui->label->setText(dst);
    ui->textEdit->setText(dst);
}

void Widget::ClipDataChanged()
{
    QString str = clipboard->text().toLocal8Bit();
    // 换行符替换为空格
    QString str2 = str.replace(QRegExp("\\n"), " ");

    QString appid = settings->value("appid").toString();
    QString key = settings->value("key").toString();
    //qDebug()<<"clip content: "<<str2;
    hr->Query("auto", "zh", str2, appid,key);
}

