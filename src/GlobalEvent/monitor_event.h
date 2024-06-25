#ifndef EVENTMONITOR_H
#define EVENTMONITOR_H
#include "QDebug"
#include "QThread"
#include <X11/Xlib.h>
#include <X11/extensions/record.h>

class EventMonitor : public QThread
{
    Q_OBJECT

  public:
    EventMonitor(QObject *parent = 0);
    virtual ~EventMonitor() override;

  signals:
    void LeftButtonRelease();

  protected:
    static void callback(XPointer trash, XRecordInterceptData *data);
    void handleRecordEvent(XRecordInterceptData *);
    void run() override;
};

#endif
