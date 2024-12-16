#include "struct.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include "memory.h"
#include "offset.h"

void gatherEntities() {
	auto& memory = getMemory();
	const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
	const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

	std::vector<Entity> entities;


	for (int i = 4;i < 128;) {
		auto entityBase = localPlayerPtr + (i * 4);

		int health = memory.Read<int>(entityBase + m_iHealth);

		char name[20];
		memory.Read(entityBase + m_iName, name, sizeof(name));

		vec3d_f position_head = memory.Read<vec3d_f>(entityBase + vec3_head);

		int team = memory.Read<int>(entityBase + iTeamNum);

		Entity entity;
		strcpy_s(entity.name, sizeof(entity.name), name);
		entity.health = health;
		entity.position_head = position_head;
		entity.team = team;

		entities.push_back(entity);
	}

	processEntities(entities);
		
}

void processEntities(const std::vector<Entity>& entities, std::uintptr_t localPlayerPtr) {
    auto& memory = getMemory();
    int iTeamNum = memory.Read<int>(localPlayerPtr + iTeamNum);

    vec3d_f localPlayerPosition = memory.Read<vec3d_f>(localPlayerPtr + vec3_head);

    Entity closestEnemy = getClosestEnemy(entities, localPlayerPosition, iTeamNum);

    std::cout << "Closest enemy coordinates: ("
        << closestEnemy.position_head.x << ", "
        << closestEnemy.position_head.y << ", "
        << closestEnemy.position_head.z << ")\n";
}

Entity getClosestEnemy(const std::vector<Entity>& entities, const vec3d_f& localPlayerPosition, int iTeamNum) {
    float closestDistance = std::numeric_limits<float>::infinity();
    Entity closestEnemy;

    for (const auto& entity : entities) {
        if (entity.team != iTeamNum && entity.health > 0) {
            float distance = sqrt(pow(entity.position_head.x - localPlayerPosition.x, 2) +
                pow(entity.position_head.y - localPlayerPosition.y, 2) +
                pow(entity.position_head.z - localPlayerPosition.z, 2));

            if (distance < closestDistance) {
                closestDistance = distance;
                closestEnemy = entity;
            }
        }
    }

    return closestEnemy;