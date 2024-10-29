#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QClipboard>
#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <qapplication.h>
#include <qevent.h>
#include <QFont>

class EngineInterface;

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
    QFont font;
};
#endif // MAINWINDOW_H
