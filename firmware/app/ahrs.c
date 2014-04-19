#include "ahrs.h"
#include "mathhelp.h"

void AhrsSetSetpoint(AhrsState *state,
                      const Vector3F *eulers) {
    QuaternionFromEulers(eulers, &state->setpoint);
}

void AhrsUpdateError(AhrsState *state,
                      const Quaternion *error,
                      float time_delta) {
    Quaternion tmp, err_delta, q_dt;
    QuaternionCopy(&state->error_p, &tmp);
    QuaternionZero(&q_dt);

    // Set error_p
    QuaternionCopy(error, &state->error_p);

    // Calculate error_d
    QuaternionDifference(error, &tmp, &err_delta);
    QuaternionLerp(&q_dt, &err_delta, 1 / time_delta, &state->error_d);

    // This only works for small values of error!
    QuaternionLerp(error, &q_dt, time_delta, &q_dt);
    QuaternionMultiply(&q_dt, &state->error_i, &state->error_i);
}

void AhrsUpdateRotFromAngVel(AhrsState *state,
                              const AhrsRotationalFloat *ang_vel,
                              float time_delta) {
    Quaternion *rot_quat = &state->r_b_to_i;

    // We are going to just scale each euler angle independently
    // and load them into a quaternion. This 'works' given that the
    // rotations are sufficiently small that the error can be ignored.
    Vector3F delta_eulers;
    Quaternion delta_quat;
    delta_eulers.a = ang_vel->roll * time_delta;
    delta_eulers.b = ang_vel->pitch * time_delta;
    delta_eulers.c = ang_vel->yaw * time_delta;
    QuaternionFromEulers(&delta_eulers, &delta_quat);

    // Update our rotational state
    QuaternionMultiply(rot_quat, &delta_quat, rot_quat);
    QuaternionNormalize(rot_quat);
}

/*! \brief Update state from angular velocity */
void AhrsUpdateFromAngVel(AhrsState *state,
                           const AhrsRotationalFloat *ang_vel,
                           float time_delta) {
    Quaternion error;
    AhrsUpdateRotFromAngVel(state, ang_vel, time_delta);
    QuaternionDifference(&state->r_b_to_i, &state->setpoint, &error);
    AhrsUpdateError(state, &error, time_delta);
}

void AhrsInit(AhrsState *s) {
    QuaternionZero(&s->r_b_to_i);
    QuaternionZero(&s->setpoint);
    QuaternionZero(&s->error_p);
    QuaternionZero(&s->error_i);
    QuaternionZero(&s->error_d);
}

