#include "mainwindow.h"
#include <QApplication>
#include <QEvent>
#include "GlobalEvent/monitor_event.h"

const QString WINDOW_TITLE("Alice Translation");

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    MainWindow main_window;
    main_window.setWindowTitle(WINDOW_TITLE);

    /*app.installEventFilter(filter);*/
    /*EventMonitor monitor;*/
    /*monitor.start();*/

    main_window.show();

    return app.exec();
}
