#pragma execution_character_set("utf-8")
#include "preference.h"
#include "ui_preference.h"
#include <QDebug>

Preference::Preference(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Preference)
{
	ui->setupUi(this);

}



Preference::Preference(QWidget* parent /*= nullptr*/, QSettings* set /*= nullptr*/) :
	QWidget(parent),
	ui(new Ui::Preference),
	settings(set)
{
	ui->setupUi(this);
	auto from = settings->value("from").toString();
	auto to = settings->value("to").toString();


	_languages[QString("auto")] = QObject::tr("自动检测");
	_languages[QString("zh")] = QObject::tr("简体中文");
	_languages[QString("cht")] = QObject::tr("繁体中文");
	_languages[QString("en")] = QObject::tr("英语");
	_languages[QString("wyw")] = QObject::tr("文言文");
	_languages[QString("yue")] = QObject::tr("粤语");
	_languages[QString("kor")] = QObject::tr("韩语");
	_languages[QString("th")] = QObject::tr("泰语");
	_languages[QString("pt")] = QObject::tr("葡萄牙语");
	_languages[QString("el")] = QObject::tr("希腊语");
	_languages[QString("bul")] = QObject::tr("保加利亚语");
	_languages[QString("fin")] = QObject::tr("芬兰语");
	_languages[QString("slo")] = QObject::tr("斯洛文尼亚语");

	_languages[QString("jp")] = QObject::tr("日语");
	_languages[QString("fra")] = QObject::tr("法语");
	_languages[QString("spa")] = QObject::tr("西班牙语");
	_languages[QString("ara")] = QObject::tr("阿拉伯语");
	_languages[QString("ru")] = QObject::tr("俄语");
	_languages[QString("de")] = QObject::tr("德语");
	_languages[QString("it")] = QObject::tr("意大利语");
	_languages[QString("nl")] = QObject::tr("荷兰语");
	_languages[QString("pl")] = QObject::tr("波兰语");
	_languages[QString("dan")] = QObject::tr("丹麦语");
	_languages[QString("cs")] = QObject::tr("捷克语");
	_languages[QString("rom")] = QObject::tr("罗马尼亚语");
	_languages[QString("swe")] = QObject::tr("瑞典语");
	_languages[QString("hu")] = QObject::tr("匈牙利语");
	_languages[QString("vie")] = QObject::tr("越南语");


	for (auto e : _languages)
	{
		ui->com_src->addItem(e.second); //不带图标
		ui->com_target->addItem(e.second);
	}

	/*for (const auto e : _languages)
	{
		if (e.second == from)
		{
			ui->com_src->setCurrentText(e.first.toLocal8Bit());
		}
		if (e.second == to)
		{
			ui->com_target->setCurrentText(e.first.toLocal8Bit());
		}
	}*/
	auto iter1 = _languages.find(from);
	auto iter2 = _languages.find(to);
	ui->com_src->setCurrentText(iter1->second);
	ui->com_target->setCurrentText(iter2->second);
}

Preference::~Preference()
{
	delete ui;
}

void Preference::Settings(QSettings* set)
{
	settings = set;
}

void Preference::on_com_src_currentIndexChanged(const QString& arg1)
{
	for (const auto e : _languages)
	{
		if (e.second == arg1)
		{
			settings->setValue(QString("from"), e.first);
			break;
		}
	}
	
}

void Preference::on_com_target_currentIndexChanged(const QString& arg1)
{
	for (const auto e : _languages)
	{
		if (e.second == arg1)
		{
			settings->setValue(QString("to"), e.first);
			break;
		}
	}
}
