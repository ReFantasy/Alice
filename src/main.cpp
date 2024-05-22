#include "mainwindow.h"
#include <QApplication>

const QString WINDOW_TITLE("Alice Translation");

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.setWindowTitle(WINDOW_TITLE);
    main_window.show();

    return app.exec();
}
