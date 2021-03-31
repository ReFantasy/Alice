#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


class QSettings;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class HttpRequest;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    /**
     * @brief 查询结果槽函数
     */
    void QueryDst(QString);

    /**
     * @brief 剪切板数据变化槽函数
     */
    void ClipDataChanged();

private:
    Ui::Widget *ui;
    HttpRequest *hr;
    QClipboard *clipboard;
    QSettings *settings;

};
#endif // WIDGET_H
