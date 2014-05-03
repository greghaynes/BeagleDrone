#ifndef CONTROL_H
#define CONTROL_H

#include "motorhelp.h"
#include "ahrs.h"

void ControlUpdateMotorState(AhrsState *state, MotorState *motors);

#endif

