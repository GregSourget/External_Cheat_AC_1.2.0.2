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
	}
		
	}