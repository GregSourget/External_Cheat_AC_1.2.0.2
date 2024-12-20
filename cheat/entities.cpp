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

void GatherEntityInfo() {
    nb_entities = GetEntityNb();
    for (int i = 0; i < nb_entities; i++) {

            /*DWORD* enemy_list = (DWORD*)(0x50F4F8);
            DWORD* enemy_offset = (DWORD*)(*enemy_list + (i * 4));
            Player* enemy = (Player*)(*enemy_offset);*/

}
