#ifndef MATH_TYPES_H
#define MATH_TYPES_H

typedef struct Vector3F {
    float a, b, c;
} Vector3F;

typedef struct Vector4F {
    float a, b, c, d;
} Vector4F;

void Vector3FZero(Vector3F *v);
void Vector4FZero(Vector4F *v);

int Vector3FEqual(const Vector3F *a, const Vector3F *b);
int Vector4FEqual(const Vector4F *a, const Vector4F *b);

#endif

