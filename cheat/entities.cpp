#include "memory.h"
#include "offset.h"
#include "struct.h"

int GetEntityCount() {
    int count = 0;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    std::uintptr_t actual_entity = memory.Read<std::uintptr_t>(entityListPtr);;

    while (actual_entity != 0) {
        Entity entity = memory.Read<Entity>(actual_entity);

        int health = memory.Read<int>(actual_entity + m_iHealth);

        if (entity.health > 0) {
            count++;
        }

        actual_entity = memory.Read<std::uintptr_t>(actual_entity + 0x4);
    }

    return count;
}
