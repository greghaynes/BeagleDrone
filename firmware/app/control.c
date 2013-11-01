#include "control.h"

static MotorState p_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

static MotorState i_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

static MotorState d_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

void ControlUpdateMotorState(State *state, MotorState *motors) {
    // P
    MotorState p_state;
    Vector3F eulers;
    QuaternionToEulers(&state->error_p, &eulers);
    MatrixMultiply3x3_4(&eulers, p_gains, &p_state);

    // I
    MotorState i_state;
    QuaternionToEulers(&state->error_i, &eulers);
    MatrixMultiply3x3_4(&eulers, i_gains, &i_state);

    // D
    MotorState d_state;
    QuaternionToEulers(&state->error_d, &eulers);
    MatrixMultiply3x3_4(&eulers, d_gains, &d_state);

    Vector4FZero(motors);
    Vector4FAdd(&p_state, motors, motors);
    Vector4FAdd(&i_state, motors, motors);
    Vector4FAdd(&d_state, motors, motors);

    MotorRescale(motors);
}

