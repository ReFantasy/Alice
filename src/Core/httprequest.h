#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <memory>
#include "translation.h"

class HttpRequest: public QObject
{
    Q_OBJECT

public:
    HttpRequest(QObject *parent = nullptr);
    ~HttpRequest(){}

    /**
     * @brief SetTranslateEngine  添加翻译引擎
     * @param engine 引擎智能指针
     */
    void SetTranslateEngine(std::shared_ptr<TranslateEngine> engine);

    /**
     * @brief Translate 翻译文本，通过私有翻译引擎生成翻译请求字符串，然后通过Http请求获取翻译结果
     * @param from 源文本语言
     * @param to 目标文本语言
     * @param src_text 源文本内容
     */
    void Translate(QString from, QString to, QString src_text);

signals:
    /**
     * @brief 完成信号，信号内容为翻译结果
     */
    void TranslateFinished(QString);

private slots:
    /**
     * @brief 解析翻译引擎的翻译结果，发送完成信号
     */
    void HttpRequestReplayFinished(QNetworkReply *);

private:
    QNetworkAccessManager *manager;
    std::shared_ptr<TranslateEngine> _tranlation_engine;
};

#endif // HTTPREQUEST_H
