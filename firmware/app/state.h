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

    Quaternion setpoint;
    Quaternion error_p;
    Quaternion error_i;
    Quaternion error_d;
} State;

void StateSetSetpoint(State *state,
                      const Vector3F *eulers);

/* Updates the rotational state given an angular velocity and time. */
void StateUpdateRotFromAngVel(State *state,
                              const StateRotationalFloat *ang_vel,
                              float time_delta);

/* Equivilent to calling these functions, in this order:
 *  StateUpdateRotFromAngVel
 */
void StateUpdateFromAngVel(State *state,
                           const StateRotationalFloat *ang_vel,
                           float time_delta);

void StateInit(State *s);

#endif
