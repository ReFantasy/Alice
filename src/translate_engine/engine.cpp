#include "engine.h"
#include "random"

unsigned int RandomUInt()
{
    std::random_device device;
    std::mt19937_64 rng(device());
    return rng();
}

bool TranslateEngine::SetIdKey(QString eng_id, QString eng_key)
{
    _id = eng_id;
    _key = eng_key;
    return true;
}

//----------------------------------------------------------------------------------------
//    
//----------------------------------------------------------------------------------------

bool BaiduEngine::SetIdKey(QString eng_id, QString eng_key)
{
    return TranslateEngine::SetIdKey(eng_id, eng_key);
}

QString BaiduEngine::WrapperAPIRequest(QString from, QString to, QString src_text)
{
    auto from_byte = from.toUtf8();
    auto to_byte = to.toUtf8();
    auto query_byte = src_text.toUtf8();
    auto appid_byte = _id.toUtf8();
    auto key_byte = _key.toUtf8();

    auto salt_byte = QString::number(RandomUInt()).toUtf8();

    auto step1_byte = appid_byte + query_byte + salt_byte + key_byte;

    auto sign_byte = QCryptographicHash::hash(step1_byte, QCryptographicHash::Md5).toHex();

    // QString http = QString("http://api.fanyi.baidu.com/api/trans/vip/translate");
    QString http = QString("https://fanyi-api.baidu.com/api/trans/vip/translate");
    QString params = QString("?q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6")
                         .arg(query_byte.toPercentEncoding(), from_byte, to_byte, appid_byte, salt_byte, sign_byte);

    return http + params;
}

QString BaiduEngine::ParseHttpReply(QString http_reply)
{
    QString all_result = http_reply;

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(all_result.toUtf8(), &error);
    if (QJsonParseError::NoError == error.error)
    {
        auto trans_result = document["trans_result"];
        auto arr = trans_result.toArray();
        auto res_array = *arr.begin();

        auto res = res_array.toObject();
        return res["dst"].toString();
    }
    return QString();
}
