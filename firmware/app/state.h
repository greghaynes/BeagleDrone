#ifndef STATE_H
#define STATE_H

#include "quaternion.h"

typedef struct StateRotationalFloat {
    float roll;
    float pitch;
    float yaw;
} StateRotationalFloat;

typedef struct StateRotationalShort {
    short roll;
    short pitch;
    short yaw;
} StateRotationalShort;

typedef struct State {
    Quaternion r_b_to_i;
    StateRotationalFloat rot_eulers;
} State;

void StateUpdateFromAngVel(State *state,
                           const StateRotationalFloat *ang_vel,
                           float time_delta);
void StateInit(State *s);

#endif
