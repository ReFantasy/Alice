#ifndef QUERYCODE_H
#define QUERYCODE_H
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <random>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

unsigned int RandomUInt();

class TranslateEngine
{
public:
    /**
     * @brief SetIdKey 设置翻译引擎的ID和密钥
     * @param eng_id
     * @param eng_key
     * @return
     */
    virtual bool SetIdKey(QString eng_id, QString eng_key) = 0;

    /**
     * @brief WrapperAPIRequest 根据翻译引擎API生成Http请求
     * @param from 源文本语言
     * @param to 目标语言
     * @param text 待翻译文本
     * @return http请求字符串
     */
    virtual QString WrapperAPIRequest(QString from, QString to, QString text) = 0;

    /**
     * @brief ParseHttpReply 解析Http请求的翻译结果
     * @param http_reply 请求返回的字符串
     * @return 翻译结果
     */
    virtual QString ParseHttpReply(QString http_reply) = 0;

protected:
    QString _id;
    QString _key;
};

class BaiduEngine:public TranslateEngine
{
public:
    bool SetIdKey(QString eng_id, QString eng_key)override;
    QString WrapperAPIRequest(QString from, QString to, QString src_text)override;

    QString ParseHttpReply(QString http_reply) override;
};




#endif // QUERYCODE_H
