#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"
#include "../cheat/aimbot.h"
#include <thread>

struct Vec3 {
    float x, y, z;
};

void RunAimbot();
Vec3 CalculateAngles(const Vec3& localPos, const Vec3& targetPos);
