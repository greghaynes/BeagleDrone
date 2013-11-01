#ifndef CONTROL_H
#define CONTROL_H

#include "motorstate.h"
#include "state.h"

void ControlUpdateMotorState(State *state, MotorState *motors);

#endif

