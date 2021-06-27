#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<QSslSocket::supportsSsl();
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    Widget w;
    w.show();
    return a.exec();
}
