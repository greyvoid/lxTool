#include "LFunc.h"

#include <QTime>
#include <QCoreApplication>


void Lx::delayTime(int s)
{
    QTime t=QTime::currentTime().addMSecs(s);
    while(QTime::currentTime()<t)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
