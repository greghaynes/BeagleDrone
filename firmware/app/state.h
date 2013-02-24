#ifndef STATE_H
#define STATE_H

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

void StateZeroRotationalShort(StateRotationalShort *state);

#endif
