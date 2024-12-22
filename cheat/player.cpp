#include <iostream>
#include "player.h"
#include "struct.h"
#include "memory.h"
#include "offset.h"

Entity playerInfo() {
	Entity player;
	auto& memory = getMemory();
	const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
	const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
	
	const auto healthAddress = localPlayerPtr + m_iHealth;
	const auto teamAddress = localPlayerPtr + iTeamNum;
	const auto headXAddress = localPlayerPtr + headX;
	const auto headYAddress = localPlayerPtr + headY;
	const auto headZAddress = localPlayerPtr + headZ;


	player.health = memory.Read<int>(healthAddress);
	player.teamNumber = memory.Read<int>(teamAddress);
	player.headPosition.x = memory.Read<float>(headXAddress);
	player.headPosition.y = memory.Read<float>(headYAddress);
	player.headPosition.z = memory.Read<float>(headZAddress);

	return player;

}