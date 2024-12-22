#include "memory.h"
#include "offset.h"
#include "struct.h"
#include <vector>
#include <iostream>
#include <cmath>

int GetEntityNb(){  
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto nb_entites = memory.Read<std::uintptr_t>(moduleBase + off_nb_entities);
    
    return nb_entites;
}

std::vector<std::uintptr_t> EntitiesOffset(){
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto entity_list = memory.Read<std::uintptr_t>(moduleBase + entityList);
    int nb_entities = GetEntityNb();

    std::vector<std::uintptr_t> entityOffsets;

    //add player to the array
    entityOffsets.push_back(localPlayerPtr);

    for (int i = 1; i < nb_entities; i++) { //i=1 to skip the first iteration, the player offset
        const auto entity_offset = memory.Read<std::uintptr_t>(entity_list + (i * sizeof(std::uintptr_t)));
        entityOffsets.push_back(entity_offset);
    }

    return entityOffsets;
}

std::vector<Entity> GetEntitiesInfo(){
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    std::vector<Entity> entities;
    std::vector<std::uintptr_t> entityOffsets = EntitiesOffset();

    for (const auto& entityOffset : entityOffsets){
        Entity entity;

        const auto healthAddress = entityOffset + m_iHealth;
        const auto teamAddress = entityOffset + iTeamNum;
        const auto headXAddress = entityOffset + headX;
        const auto headYAddress = entityOffset + headY;
        const auto headZAddress = entityOffset + headZ;

        entity.health = memory.Read<int>(healthAddress);
        entity.teamNumber = memory.Read<int>(teamAddress);
        entity.headPosition.x = memory.Read<float>(headXAddress);
        entity.headPosition.y = memory.Read<float>(headYAddress);
        entity.headPosition.z = memory.Read<float>(headZAddress);

        entities.push_back(entity);
    }

    return entities;
}

Vector3 GetClosestEnemyPos() {
    std::vector<Entity> entities = GetEntitiesInfo();

    float closestDistance = 99999;

    Entity localPlayer = entities[0];

    float localX = localPlayer.headPosition.x;
    float localY = localPlayer.headPosition.y;
    float localZ = localPlayer.headPosition.z;
    int localTeam = localPlayer.teamNumber;

    Vector3 closestEnemy;

    for (size_t i = 1; i < entities.size(); ++i) {
        const auto& entity = entities[i];   //I use const auto to prevent my coordinates from being updated and distorting the comparison btw
        if (entity.teamNumber == localTeam) {
            continue;
        }

        float distance = std::sqrt(std::pow(localX - entity.headPosition.x, 2) + std::pow(localY - entity.headPosition.y, 2) + std::pow(localZ - entity.headPosition.z, 2));

        if (distance < closestDistance) {
            closestDistance = distance;

            closestEnemy.x = entity.headPosition.x;
            closestEnemy.y = entity.headPosition.y;
            closestEnemy.z = entity.headPosition.z;
        }
    }
    return closestEnemy;
}