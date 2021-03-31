#include <QNetworkAccessManager>
#include <QClipboard>
#include <QSettings>
#include <QDebug>
#include <QMenu>
#include <QCloseEvent>
#include "widget.h"
#include "ui_widget.h"

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
    qDebug()<<QCoreApplication::applicationDirPath();
    if(settings->value("appid").isNull())
    {
        settings->setValue("appid", "your_appid");
    }
    if(settings->value("key").isNull())
    {
        settings->setValue("key", "your_key");
    }

    // SystemTray Setting
    systemTray = new QSystemTrayIcon(this);
    systemTray->setToolTip("Alice Translation");
    systemTray->setIcon(QIcon(":/images/Images/logo.png"));
    systemTray->setVisible(true);

    // Tray Menu
    QMenu* tray_menu = new QMenu();
    tray_menu->addSeparator();
    auto close_app_action = new QAction(tray_menu);
    close_app_action->setText("Quit");
    tray_menu->addAction(close_app_action);
    connect(close_app_action, &QAction::triggered, this, &Widget::CloseApp);
    systemTray->setContextMenu(tray_menu);

    //preference

    // Connect Tray signals
    connect(systemTray, &QSystemTrayIcon::activated, this, &Widget::OnSystemTrayClicked);//点击托盘，执行相应的动作
    systemTray->show();

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

void Widget::QueryDst(QString dst)
{
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

void Widget::CloseApp()
{
    exit(0);
}

