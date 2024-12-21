#include "memory.h"
#include "offset.h"
#include "struct.h"
#include <iostream>
#include <windows.h>

int GetEntityNb() {  
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto nb_entites = memory.Read<std::uintptr_t>(moduleBase + off_nb_entities);
    
    return nb_entites;
}

std::vector<std::uintptr_t> GatherEntityInfo() {
    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entity_list = memory.Read<std::uintptr_t>(moduleBase + entityList);
    int nb_entities = GetEntityNb();
    std::vector<std::uintptr_t> entityOffsets;

    for (int i = 0; i < nb_entities; i++) {
        const auto entity_offset = memory.Read<std::uintptr_t>(entity_list + (i * sizeof(std::uintptr_t)));
        entityOffsets.push_back(entity_offset);
    }

    return entityOffsets;
}
