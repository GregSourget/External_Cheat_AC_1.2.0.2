#pragma once
#include <vector>
#include "struct.h"

int GetEntityNb();
std::vector<std::uintptr_t> EntitiesOffset();
std::vector<Entity> GetEntitiesInfo();
