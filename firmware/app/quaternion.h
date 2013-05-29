#ifndef QUATERNION_H
#define QUATERNION_H

#include "mathhelp.h"

typedef Vector4F Quaternion;

void QuaternionZero(Quaternion *q);
void QuaternionCopy(const Quaternion *src, Quaternion *dest);
void QuaternionNormalize(Quaternion *q);
void QuaternionConjugate(Quaternion *q);
void QuaternionInvert(Quaternion *q);
void QuaternionFromEulers(const Vector3F *eulers, Quaternion *q);
void QuaternionToEulers(const Quaternion *q, Vector3F *dest);
void QuaternionMultiply(const Quaternion *q,
                        const Quaternion *r,
                        Quaternion *t);
void QuaternionDifference(const Quaternion *a,
                          const Quaternion *b,
                          Quaternion *dest);
float QuaternionDotProduct(const Quaternion *a,
                           const Quaternion *b);
void QuaternionLerp(const Quaternion *a,
                    const Quaternion *b,
                    float t,
                    Quaternion *dest);


#endif
