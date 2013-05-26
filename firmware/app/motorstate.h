#ifndef MOTOR_STATE_H
#define MOTOR_STATE_H

#include "mathhelp.h"
#include "state.h"

typedef Vector4F MotorState;

void MotorStateInit(MotorState *s);
void MotorStateUpdate(MotorState *motors,
                      State *state);

#endif
