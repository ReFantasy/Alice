#include "interface.h"
#include <QDebug>
HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &HttpRequest::HttpRequestReplayFinished);
}

void HttpRequest::HttpRequestReplayFinished(QNetworkReply *reply)
{
    QString request_result = reply->readAll();
    emit RequestFinished(request_result);
}

EngineInterface::EngineInterface(QObject *parent) : QObject(parent)
{
    connect(&http_request, &HttpRequest::RequestFinished, this, &EngineInterface::HttpRequestResult);
}

void EngineInterface::SetTranslateEngine(std::shared_ptr<TranslateEngine> engine)
{
    _tranlation_engine = engine;
}

void EngineInterface::Translate(QString from, QString to, QString src_text)
{

    if (!_tranlation_engine)
    {
        throw "no translation engin";
    }
    QString http_require_str = _tranlation_engine->WrapperAPIRequest(from, to, src_text);
    //  将翻译请求通过 http 发送
    http_request.manager->get(QNetworkRequest(QUrl(http_require_str)));
}

void EngineInterface::HttpRequestResult(QString s)
{
    // 接受 http 请求结果，解析后发给前端
    QString Translated_text = _tranlation_engine->ParseHttpReply(s);
    emit TranslateFinished(Translated_text);
}
