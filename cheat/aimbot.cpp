#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"
#include "../cheat/aimbot.h"
#include <thread>

constexpr double M_PI = 3.141592653;

Vec3 CalculateAngles(const Vec3& localPos, const Vec3& targetPos) {
    // Calcul des différences de coordonnées
    Vec3 delta = { targetPos.x - localPos.x, targetPos.y - localPos.y, /*targetPos.z - localPos.z*/};

    // Calcul de la distance horizontale (sur le plan XY)
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y /* + delta.z * delta.z */);

    float pitch = static_cast<float>(-std::atan2(delta.z, distance) * (180.0 / M_PI));
    float yaw = static_cast<float>(std::atan2(delta.y, delta.x) * (180.0 / M_PI));

    // Retourner les angles calculés (pitch, yaw, roll) - ici roll est inutile et mis à 0
    return { pitch, yaw, 0.0f };
}

void RunAimbot() {
    auto& memory = getMemory();

    uintptr_t moduleBase = memory.GetModuleAddress("ac_client.exe"); 
    if (!moduleBase) {
        std::cerr << "Erreur : module introuvable !" << std::endl;
        return;
    }

    uintptr_t localPlayerAddr = memory.Read<uintptr_t>(moduleBase + localPlayer);
    if (!localPlayerAddr) {
        OutputDebugStringA("joueur introuvable\n");
        std::cerr << "Erreur : joueur local introuvable !" << std::endl;
        return;
    }

    Vec3 localPos = memory.Read<Vec3>(localPlayerAddr + m_vecOrigin);
    int localTeam = memory.Read<int>(localPlayerAddr + team);

    for (int i = 0; i < 32; ++i) {
        uintptr_t entity = memory.Read<uintptr_t>(moduleBase + entityList + i * 0x10);
        if (entity == 0) continue;

        int entityHealth = memory.Read<int>(entity + m_iHealth);
        auto entityTeam = memory.Read<int>(entity + team);

        if (entityHealth > 0 && entityTeam != localTeam) {
            OutputDebugStringA("testtt\n");
            Vec3 targetPos = memory.Read<Vec3>(entity + headPos);
            Vec3 aimAngles = CalculateAngles(localPos, targetPos);

            memory.Write<float>(localPlayerAddr + yaw, aimAngles.y);
            memory.Write<float>(localPlayerAddr + pitch, aimAngles.x);
            OutputDebugStringA("testyaw et pitch\n");

        }
    }
}
