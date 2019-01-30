#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "searchfiles.h"

class Observer {
public:
    int CheckStatus();
};

class StartThread : public QThread {
    Q_OBJECT
    SearchFiles* s_ptr_;
public:
    StartThread (SearchFiles* ptr);
    void run();
};

class StopThread : public QThread {
    Q_OBJECT
    SearchFiles* s_ptr_;
public:
    StopThread (SearchFiles* ptr);
    void run();
};

#endif // CONTROLLER_H
