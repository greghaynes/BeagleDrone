#include "motorstate.h"

/*
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
*/

void MotorStateInit(MotorState *s) {
    Vector4FZero(s);
}

void MotorStateUpdate(MotorState *motors,
                      State *state) {
    // P
}

