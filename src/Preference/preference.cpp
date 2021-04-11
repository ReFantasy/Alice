#pragma execution_character_set("utf-8")
#include "preference.h"
#include "ui_preference.h"
#include <QDebug>

Preference::Preference(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);

}

Preference::Preference(QWidget *parent, QSettings *set):
    QWidget(parent),
    ui(new Ui::Preference),
    settings(set)
{
        ui->setupUi(this);


        _languages[QString("自动检测")] = QString("auto");
        _languages[QString("简体中文")] = QString("zh");
        _languages[QString("繁体中文")] = QString("cht");
        _languages[QString("英语")] = QString("en");
        _languages[QString("文言文")] = QString("wyw");
        _languages[QString("粤语")] = QString("yue");
        _languages[QString("韩语")] = QString("kor");
        _languages[QString("泰语")] = QString("th");
        _languages[QString("葡萄牙语")] = QString("pt");
        _languages[QString("希腊语")] = QString("el");
        _languages[QString("保加利亚语")] = QString("bul");
        _languages[QString("芬兰语")] = QString("fin");
        _languages[QString("斯洛文尼亚语")] = QString("slo");

        _languages[QString("日语")] = QString("jp");
        _languages[QString("法语")] = QString("fra");
        _languages[QString("西班牙语")] = QString("spa");
        _languages[QString("阿拉伯语")] = QString("ara");
        _languages[QString("俄语")] = QString("ru");
        _languages[QString("德语")] = QString("de");
        _languages[QString("意大利语")] = QString("it");
        _languages[QString("荷兰语")] = QString("nl");
        _languages[QString("波兰语")] = QString("pl");
        _languages[QString("丹麦语")] = QString("dan");
        _languages[QString("捷克语")] = QString("cs");
        _languages[QString("罗马尼亚语")] = QString("rom");
        _languages[QString("瑞典语")] = QString("swe");
        _languages[QString("匈牙利语")] = QString("hu");
        _languages[QString("越南语")] = QString("vie");

        for(auto e:_languages)
        {
            ui->com_src->addItem(e.first); //不带图标
            ui->com_target->addItem(e.first);
        }

        for(const auto e:_languages)
        {
            qDebug()<<this->settings->value("from").toString();
            if(e.second == this->settings->value("from").toString())
            {
                ui->com_src->setCurrentText(e.first);
            }
            if(e.second == this->settings->value("to").toString())
            {
                ui->com_target->setCurrentText(e.first);
            }
        }

}

Preference::~Preference()
{
    delete ui;
}

void Preference::on_com_src_currentIndexChanged(const QString &arg1)
{
    settings->setValue(QString("from"),_languages[arg1]);
}

void Preference::on_com_target_currentIndexChanged(const QString &arg1)
{
    settings->setValue(QString("to"),_languages[arg1]);
}
