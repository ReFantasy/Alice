//#pragma execution_character_set("utf-8")
#include "preference.h"
#include "ui_preference.h"
#include <QDebug>

Preference::Preference(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);

}



Preference::~Preference()
{
    delete ui;
}

void Preference::Settings(QSettings *set)
{
    settings = set;

    _languages[QObject::tr("自动检测")] = QString("auto");
    _languages[QObject::tr("简体中文")] = QString("zh");
    _languages[QObject::tr("繁体中文")] = QString("cht");
    _languages[QObject::tr("英语")] = QString("en");
    _languages[QObject::tr("文言文")] = QString("wyw");
    _languages[QObject::tr("粤语")] = QString("yue");
    _languages[QObject::tr("韩语")] = QString("kor");
    _languages[QObject::tr("泰语")] = QString("th");
    _languages[QObject::tr("葡萄牙语")] = QString("pt");
    _languages[QObject::tr("希腊语")] = QString("el");
    _languages[QObject::tr("保加利亚语")] = QString("bul");
    _languages[QObject::tr("芬兰语")] = QString("fin");
    _languages[QObject::tr("斯洛文尼亚语")] = QString("slo");

    _languages[QObject::tr("日语")] = QString("jp");
    _languages[QObject::tr("法语")] = QString("fra");
    _languages[QObject::tr("西班牙语")] = QString("spa");
    _languages[QObject::tr("阿拉伯语")] = QString("ara");
    _languages[QObject::tr("俄语")] = QString("ru");
    _languages[QObject::tr("德语")] = QString("de");
    _languages[QObject::tr("意大利语")] = QString("it");
    _languages[QObject::tr("荷兰语")] = QString("nl");
    _languages[QObject::tr("波兰语")] = QString("pl");
    _languages[QObject::tr("丹麦语")] = QString("dan");
    _languages[QObject::tr("捷克语")] = QString("cs");
    _languages[QObject::tr("罗马尼亚语")] = QString("rom");
    _languages[QObject::tr("瑞典语")] = QString("swe");
    _languages[QObject::tr("匈牙利语")] = QString("hu");
    _languages[QObject::tr("越南语")] = QString("vie");

    for(auto e:_languages)
    {
        ui->com_src->addItem(e.first); //不带图标
        ui->com_target->addItem(e.first);
    }


    for(const auto e:_languages)
    {
        qDebug()<<settings->value("from").toString();

        if(e.second.toLocal8Bit() == settings->value("from").toString().toLocal8Bit())
        {
            ui->com_src->setCurrentText(e.first);
        }
        if(e.second.toLocal8Bit() == settings->value("to").toString().toLocal8Bit())
        {
            ui->com_target->setCurrentText(e.first);
        }
    }
}

void Preference::on_com_src_currentIndexChanged(const QString &arg1)
{
    settings->setValue(QString("from"),_languages[arg1]);
}

void Preference::on_com_target_currentIndexChanged(const QString &arg1)
{
    settings->setValue(QString("to"),_languages[arg1]);
}
