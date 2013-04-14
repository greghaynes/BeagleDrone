#ifndef QUATERNION_H
#define QUATERNION_H

#include "mathtypes.h"

typedef Vector4F Quaternion;

void QuaternionFromEulers(const Vector3F *eulers, Quaternion *q);
void QuaternionToEulers(const Quaternion *q, Vector3F *dest);
void QuaternionMultiply(const Quaternion *q,
                        const Quaternion *r,
                        Quaternion *t);

#endif
