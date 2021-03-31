#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>

#include "querycode.h"

class HttpRequest: public QObject
{
    Q_OBJECT

public:
    HttpRequest(QObject *parent = nullptr);
    ~HttpRequest(){}


    void Query(QString from, QString to, QString query, QString appid, QString key)
    {
        QueryCode qc;
        auto qstr = qc.Gen(from, to, query, appid,key);
        manager->get(QNetworkRequest(QUrl(qstr)));
    }

signals:
    void QueryDst(QString);

private slots:
    void replayFinished(QNetworkReply *);

private:
    QNetworkAccessManager *manager;
};

#endif // HTTPREQUEST_H
