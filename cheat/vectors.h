#pragma once
#include <cmath> 

struct Vector3 {
    float x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

struct Vector2 {
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
};

//Constantes

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double degreeToRadian = M_PI / 180.0;   // degrés to radians
const double anglesOffset = 90 * degreeToRadian;


