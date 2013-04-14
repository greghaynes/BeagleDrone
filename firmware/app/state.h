#ifndef STATE_H
#define STATE_H

#include "quaternion.h"

typedef struct RotationalFloat {
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
} StateFull;

void StateZeroRotationalShort(StateRotationalShort *state);

#endif
