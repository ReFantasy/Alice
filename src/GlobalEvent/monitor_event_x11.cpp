#include "monitor_event.h"
#include <X11/X.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>

void EventMonitor::callback(XPointer ptr, XRecordInterceptData *data)
{
    ((EventMonitor *)ptr)->handleRecordEvent(data);
}
void EventMonitor::handleRecordEvent(XRecordInterceptData *data)
{
    auto filterWheelEvent = [](int detail) {
        /*return detail != WheelUp && detail != WheelDown && detail != WheelLeft &&
         * detail != WheelRight;*/
    };

    /*QProcess process;*/
    if (data->category == XRecordFromServer)
    {
        auto xev = (XEvent *)data->data;
        /*qDebug()<<xev->type;*/
        switch (xev->type)
        {
        case 261:
            // Request the Primary Selection clipboard contents
            emit LeftButtonRelease();
        default:
            static int n = 0;
            /*qDebug() << n++;*/
            /*qDebug()<<xev->type;*/
        }
    }
    fflush(stdout);
    XRecordFreeData(data);
}
EventMonitor::EventMonitor(QObject *parent) : QThread(parent)
{
    /*Window root_window = DefaultRootWindow(dpy);*/
    /*XSelectInput(dpy, root_window, KeyPressMask | KeyReleaseMask |
     * ButtonPressMask | ButtonReleaseMask);*/
}

EventMonitor::~EventMonitor()
{
}

void EventMonitor::run()
{
    qDebug() << "thread start";

    Display *display = XOpenDisplay(0);
    if (display == 0)
    {
        fprintf(stderr, "unable to open display\n");
        return;
    }

    // Receive from ALL clients, including future clients.
    XRecordClientSpec clients = XRecordAllClients;
    XRecordRange *range = XRecordAllocRange();
    if (range == 0)
    {
        fprintf(stderr, "unable to allocate XRecordRange\n");
        return;
    }

    // Receive KeyPress, KeyRelease, ButtonPress, ButtonRelease and MotionNotify
    // events.
    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last = MotionNotify;

    // And create the XRECORD context.
    XRecordContext context = XRecordCreateContext(display, 0, &clients, 1, &range, 1);
    if (context == 0)
    {
        fprintf(stderr, "XRecordCreateContext failed\n");
        return;
    }
    XFree(range);
    XSync(display, True);

    Display *display_datalink = XOpenDisplay(0);
    if (display_datalink == 0)
    {
        fprintf(stderr, "unable to open second display\n");
        return;
    }

    if (!XRecordEnableContext(display_datalink, context, callback, (XPointer)this))
    {
        fprintf(stderr, "XRecordEnableContext() failed\n");
        return;
    }
    qDebug() << "thread end";
}
