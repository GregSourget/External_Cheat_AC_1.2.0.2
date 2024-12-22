#include "memory.h"
#include "offset.h"
#include "struct.h"
#include <vector>
#include <iostream>
#include <cmath>

int GetEntityNb() {  
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto nb_entites = memory.Read<std::uintptr_t>(moduleBase + off_nb_entities);
    
    return nb_entites;
}

std::vector<std::uintptr_t> EntitiesOffset() {
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto entity_list = memory.Read<std::uintptr_t>(moduleBase + entityList);
    int nb_entities = GetEntityNb();

    std::vector<std::uintptr_t> entityOffsets;

    //add player to the array
    //const auto player_offset = memory.Read<std::uintptr_t>(localPlayerPtr);
    entityOffsets.push_back(localPlayerPtr);

    for (int i = 1; i < nb_entities; i++) { //i=1 to skip the 1st iteration, the player offset
        const auto entity_offset = memory.Read<std::uintptr_t>(entity_list + (i * sizeof(std::uintptr_t)));
        entityOffsets.push_back(entity_offset);
    }

    return entityOffsets;
}

std::vector<Entity> GetEntitiesInfo() {
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    std::vector<Entity> entities;
    std::vector<std::uintptr_t> entityOffsets = EntitiesOffset();

    for (const auto& entityOffset : entityOffsets) {
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

Entity GetClosestPlayer() {
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    // Obtenir l'adresse du joueur local
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    // Obtenir la position du joueur local
    const auto localHeadX = localPlayerPtr + headX;
    const auto localHeadY = localPlayerPtr + headY;
    const auto localHeadZ = localPlayerPtr + headZ;

    // Lire les positions du joueur local
    const float localX = memory.Read<float>(localHeadX);
    const float localY = memory.Read<float>(localHeadY);
    const float localZ = memory.Read<float>(localHeadZ);

    // Obtenir toutes les entités
    std::vector<std::uintptr_t> entityOffsets = EntitiesOffset();

    Entity closestPlayer;
    float closestDistance = FLT_MAX; // Distance initiale infinie pour trouver le plus proche

    for (const auto& entityOffset : entityOffsets) {
        // Lire les informations de l'entité (joueur) en cours
        const auto healthAddress = entityOffset + m_iHealth;
        const auto teamAddress = entityOffset + iTeamNum;
        const auto headXAddress = entityOffset + headX;
        const auto headYAddress = entityOffset + headY;
        const auto headZAddress = entityOffset + headZ;

        int health = memory.Read<int>(healthAddress);
        int team = memory.Read<int>(teamAddress);
        float headX = memory.Read<float>(headXAddress);
        float headY = memory.Read<float>(headYAddress);
        float headZ = memory.Read<float>(headZAddress);

        // Ignorer le joueur local
        if (health <= 0 || team == localPlayerTeam) { // Remplacez `localPlayerTeam` par l'équipe du joueur local
            continue;
        }

        // Calculer la distance euclidienne entre le joueur local et l'entité
        float distance = std::sqrt(
            std::pow(localX - headX, 2) +
            std::pow(localY - headY, 2) +
            std::pow(localZ - headZ, 2)
        );

        // Si cette entité est plus proche que la précédente, mettre à jour la plus proche
        if (distance < closestDistance) {
            closestDistance = distance;
            closestPlayer.health = health;
            closestPlayer.teamNumber = team;
            closestPlayer.headPosition.x = headX;
            closestPlayer.headPosition.y = headY;
            closestPlayer.headPosition.z = headZ;
        }
    }

    return closestPlayer;
}
