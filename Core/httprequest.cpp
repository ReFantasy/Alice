#include "httprequest.h"

HttpRequest::HttpRequest(QObject *parent)
    :QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &HttpRequest::HttpRequestReplayFinished);
}

void HttpRequest::SetTranslateEngine(std::shared_ptr<TranslateEngine> engine)
{
    _tranlation_engine = engine;
}

void HttpRequest::Translate(QString from, QString to, QString src_text)
{
    QString http_require_str = _tranlation_engine->WrapperAPIRequest(from, to, src_text);
    manager->get(QNetworkRequest(QUrl(http_require_str)));
}

void HttpRequest::HttpRequestReplayFinished(QNetworkReply *reply)
{
    QString all_result = reply->readAll();
    QString Translated_text = _tranlation_engine->ParseHttpReply(all_result);
    emit TranslateFinished(Translated_text);
}
