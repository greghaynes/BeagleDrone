#ifndef MOTOR_STATE_H
#define MOTOR_STATE_H

#include "mathhelp.h"
#include "ahrs.h"

typedef Vector4F MotorState;

void MotorRescale(MotorState *s);

#endif

