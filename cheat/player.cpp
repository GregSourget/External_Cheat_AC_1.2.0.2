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

	player.health = memory.Read<int>(healthAddress);
	return player;

}