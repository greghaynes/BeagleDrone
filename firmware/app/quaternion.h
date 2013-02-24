#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct Quaternion {
    float a;
    float b;
    float c;
    float d;
} Quaternion;

void QuaternionFromEulers(float a, float b, float c, Quaternion *q);
void QuaternionMultiply(const Quaternion *q,
                        const Quaternion *r,
                        Quaternion *t);

#endif
