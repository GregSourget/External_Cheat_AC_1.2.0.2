#pragma once

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;

class Entity {
public:
    int health;
    Vector3 headPosition;
    Vector3 feetPosition;
    char name[20];
    int teamNumber;
};