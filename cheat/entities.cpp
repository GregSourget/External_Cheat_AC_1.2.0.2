#include "memory.h"
#include "offset.h"
#include "struct.h"
#include <iostream>
#include <windows.h>
//297a120

int GetEntityCount() {

    AllocConsole();
    FILE* pFile;
    if (freopen_s(&pFile, "CONOUT$", "w", stdout) != 0) {
        std::cerr << "Failed to redirect stdout to console." << std::endl;
    }
    if (freopen_s(&pFile, "CONOUT$", "w", stderr) != 0) {
        std::cerr << "Failed to redirect stderr to console." << std::endl;
    }
    int count = 0;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto actual_entity = entityListPtr + entities_off + entities_off;

    //ca ne marche pas car je parcour ma premiere entité ,

    while (actual_entity != 0) {
        std::cout << "Entity Address: " << std::hex << actual_entity << std::dec << std::endl;


        /*Entity entity = memory.Read<Entity>(actual_entity);
        int health = memory.Read<int>(actual_entity + m_iHealth);

        if (entity.health > 0) {
            count++;
        }*/
        count++;
        const auto actual_entity = entityListPtr + entities_off;

    }

    return count;
}
