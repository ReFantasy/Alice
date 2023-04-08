#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Preference/preference.h"
#include "translate_engine/interface.h"
#include <QClipboard>
#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief 点击红叉时隐藏主界面
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

  private slots:
    /**
     * @brief 接受翻译解雇槽函数
     */
    void ReceiveTranslatedResult(QString);

  private:
    void InitSystemTray();

  private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *systemTray;
    QClipboard *clipboard;
    QSettings *settings;
    EngineInterface *engine_interface;
    Preference *preference;
};
#endif // MAINWINDOW_H
