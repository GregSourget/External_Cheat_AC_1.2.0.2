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





//rajouter une fonction dans ce fichier pour chopper l'ennemie le plus proche et 
// ameliorer celle existence pour chopper toute les infos avec la struct entity

