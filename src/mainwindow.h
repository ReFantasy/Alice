#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "interface.h"
#include <QClipboard>
#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <qapplication.h>
#include <qevent.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);

  private slots:
    void ShowTranslatedResult(QString);

  private:
    EngineInterface *engine_interface;

  private:
    QTextEdit *textEdit;
    QSettings *settings;
};
#endif // MAINWINDOW_H
