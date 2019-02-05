#ifndef STATECHECKER_H
#define STATECHECKER_H

#include <QMutex>
#include <QThread>
#include "general.h"

class StateChecker : public QObject
{
protected:
    Process state_;
public:
    StateChecker();
    Process Check();
    void SetState(Process state);
};

#endif // STATECHECKER_H
