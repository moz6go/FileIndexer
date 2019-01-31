#include "statechecker.h"

StateChecker::StateChecker(): state_(DEFAULT) {}

Process StateChecker::Check() {
    return state_;
}

void StateChecker::SetState(Process state) {
    state_ = state;
}