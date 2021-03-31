#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

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


    /**
     * @brief 重载关闭事件，点击红叉时隐藏主界面
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * @brief 查询结果槽函数
     */
    void QueryDst(QString);

    /**
     * @brief 剪切板数据变化槽函数
     */
    void ClipDataChanged();

private slots:
    /**
     * @brief 处理系统托盘信号
     * @param reason
     */
    void OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);

    /**
     * @brief CloseApp 相应托盘动作，关闭应用
     */
    void CloseApp();

    /**
     * @brief SetPreference 偏好设置
     */
    void SetPreference();

private:
    Ui::Widget *ui;
    HttpRequest *hr;
    QClipboard *clipboard;
    QSettings *settings;

    // 系统托盘
    QSystemTrayIcon *systemTray;

};
#endif // WIDGET_H
