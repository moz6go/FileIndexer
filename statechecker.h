#ifndef STATECHECKER_H
#define STATECHECKER_H

#include "general.h"

class StateChecker : public QObject
{
protected:
    QMutex state_sync_;
    Condition state_;
public:
    StateChecker();
    Condition Check();
    void SetState(Condition state);
};

#endif // STATECHECKER_H
