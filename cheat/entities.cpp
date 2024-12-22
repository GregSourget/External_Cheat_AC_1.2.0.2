#include "memory.h"
#include "offset.h"
#include "struct.h"
#include <vector>
#include <iostream>

int GetEntityNb() {  
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto nb_entites = memory.Read<std::uintptr_t>(moduleBase + off_nb_entities);
    
    return nb_entites;
}

std::vector<std::uintptr_t> EntitiesOffset() {
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entity_list = memory.Read<std::uintptr_t>(moduleBase + entityList);
    int nb_entities = GetEntityNb();

    std::vector<std::uintptr_t> entityOffsets;

    for (int i = 0; i < nb_entities; i++) {
        const auto entity_offset = memory.Read<std::uintptr_t>(entity_list + (i * sizeof(std::uintptr_t)));
        entityOffsets.push_back(entity_offset);
    }


    //ok je veux une boucle for qui prend en arguments le nombre d'entitées 
    //et qui recupere comme dans player.cpp toutes les infos 
    //et voila 

    //remove the first offset who reffer to currentPLayer 0x000000
    /*if (!entityOffsets.empty()) {
        entityOffsets.erase(entityOffsets.begin());
    }*/
    return entityOffsets;
}





//rajouter une fonction dans ce fichier pour chopper l'ennemie le plus proche et 
// ameliorer celle existence pour chopper toute les infos avec la struct entity

