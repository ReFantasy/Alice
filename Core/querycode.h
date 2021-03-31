#ifndef QUERYCODE_H
#define QUERYCODE_H
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <random>

unsigned int RandomUInt();

class QueryCode
{
public:
    QueryCode()=default;

    QString Gen(QString from, QString to, QString query, QString appid, QString key)
    {
        auto from_byte = from.toUtf8();
        auto to_byte = to.toUtf8();
        auto query_byte = query.toUtf8();
        auto appid_byte = appid.toUtf8();
        auto key_byte = key.toUtf8();

        auto salt_byte = QString::number(RandomUInt()).toUtf8();

        auto step1_byte = appid_byte+query_byte+salt_byte+key_byte;

        auto sign_byte = QCryptographicHash::hash(step1_byte,QCryptographicHash::Md5).toHex();

        QString http = QString("http://api.fanyi.baidu.com/api/trans/vip/translate");
        QString params = QString("?q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6")
                .arg(query_byte.toPercentEncoding(),from_byte, to_byte, appid_byte, salt_byte, sign_byte);

        return http+params;
    }
};




#endif // QUERYCODE_H
