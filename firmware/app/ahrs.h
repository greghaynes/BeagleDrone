#ifndef AHRS_H
#define AHRS_H

#include "quaternion.h"

typedef struct AhrsRotationalFloat {
    float roll;
    float pitch;
    float yaw;
} AhrsRotationalFloat;

typedef struct AhrsRotationalShort {
    short roll;
    short pitch;
    short yaw;
} AhrsRotationalShort;

typedef struct AhrsState {
    Quaternion r_b_to_i;

    Quaternion setpoint;
    Quaternion error_p;
    Quaternion error_i;
    Quaternion error_d;
} AhrsState;

void AhrsSetSetpoint(AhrsState *state,
                      const Vector3F *eulers);

void AhrsUpdateError(AhrsState *state,
                      const Quaternion *error,
                      float time_delta);

/* Updates the rotational state given an angular velocity and time. */
void AhrsUpdateRotFromAngVel(AhrsState *state,
                              const AhrsRotationalFloat *ang_vel,
                              float time_delta);

/* Equivilent to calling these functions, in this order:
 *  AhrsUpdateRotFromAngVel
 *  AhrsUpdateError
 *
 *  This is useful for testing but typically the error and motors are not
 *  updated at the same rate as rotational state.
 */
void AhrsUpdateFromAngVel(AhrsState *state,
                           const AhrsRotationalFloat *ang_vel,
                           float time_delta);

void AhrsInit(AhrsState *s);

#endif
