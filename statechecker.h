#ifndef STATECHECKER_H
#define STATECHECKER_H
#include "myenums.h"

class StateChecker
{
protected:
    Process state_;
public:
    StateChecker();
    Process Check();
    void SetState(Process state);
};

#endif // STATECHECKER_H
