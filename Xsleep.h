#ifndef XSLEEP_H
#define    XSLEEP_H

#include <QThread>

class Xsleep : public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};

#endif
