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

typedef Vector4F MotorState;

typedef struct State {
    Quaternion r_b_to_i;

    Quaternion setpoint;
    Quaternion error_p;
    Quaternion error_i;
    Quaternion error_d;

    MotorState motor_state;
} State;

void StateSetSetpoint(State *state,
                      const Vector3F *eulers);

void StateUpdateError(State *state,
                      const Quaternion *error,
                      float time_delta);

/* Updates the rotational state given an angular velocity and time. */
void StateUpdateRotFromAngVel(State *state,
                              const StateRotationalFloat *ang_vel,
                              float time_delta);

void StateUpdateMotors(State *state);

/* Equivilent to calling these functions, in this order:
 *  StateUpdateRotFromAngVel
 *  StateUpdateError
 *  StateUpdateMotors
 *
 *  This is useful for testing but typically the error and motors are not
 *  updated at the same rate as rotational state.
 */
void StateUpdateFromAngVel(State *state,
                           const StateRotationalFloat *ang_vel,
                           float time_delta);

void StateInit(State *s);

#endif
