#include "httprequest.h"

HttpRequest::HttpRequest(QObject *parent)
    :QObject(parent)
{
    manager = new QNetworkAccessManager;

    connect(manager, &QNetworkAccessManager::finished,
            this, &HttpRequest::replayFinished);
}

void HttpRequest::replayFinished(QNetworkReply *reply)
{
    QString all_result = reply->readAll();
    qDebug()<<all_result;
    reply->deleteLater();

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(all_result.toUtf8(), &error);
    if(QJsonParseError::NoError == error.error)
    {
        qDebug()<<document["from"];
        qDebug()<<document["to"];
        auto trans_result = document["trans_result"];
        //qDebug()<<trans_result.isArray();
        auto arr = trans_result.toArray();
        auto res_array = *arr.begin();


        auto res = res_array.toObject();
        //qDebug()<<res["src"];
        //qDebug()<<res["dst"].toString();
        emit QueryDst(res["dst"].toString());
        return;
    }

    //qDebug()<<"start emit signals";
    emit QueryDst(QString(""));
    return;
}
