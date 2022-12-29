#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include "engine.h"
#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetwork>
#include <memory>

class HttpRequest : public QObject
{
    Q_OBJECT

  public:
    HttpRequest(QObject *parent = nullptr);
    ~HttpRequest()
    {
    }

  private slots:
    /**
     * @brief 网络请求槽函数
     */
    void HttpRequestReplayFinished(QNetworkReply *);

  signals:
    /**
     * @brief 发送网络请求结束信号
     */
    void RequestFinished(QString);

  public:
    QNetworkAccessManager *manager;
};

class EngineInterface : public QObject
{
    Q_OBJECT
  public:
    EngineInterface(QObject *parent = nullptr);
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

  private slots:
    /**
     * @brief 接受Http完成信号
     */
    void HttpRequestResult(QString s);

  signals:
    /**
     * @brief 将最终结果发送给前端界面
     */
    void TranslateFinished(QString);

  private:
    std::shared_ptr<TranslateEngine> _tranlation_engine;
    HttpRequest http_request;
};

#endif // __HTTPREQUEST_H__
