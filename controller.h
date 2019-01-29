#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "searchfiles.h"

class StartThread : public QThread {
    Q_OBJECT
public:
    void run();
signals:
    void indx_ends(QString);
};


class StopThread : public QThread {
    Q_OBJECT
public:
    void run();
};


#endif // CONTROLLER_H
