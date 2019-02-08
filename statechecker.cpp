#include "statechecker.h"

StateChecker::StateChecker(): state_(DEFAULT) {}

Condition StateChecker::Check() {
    return state_;
}

void StateChecker::SetState(Condition state) {
    QMutex mtx;
    mtx.lock ();
    state_ = state;
    mtx.unlock ();
}
