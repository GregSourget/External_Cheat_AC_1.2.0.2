#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"


int cheat::updatedHealth = 100; //initalisation
int cheat::updatedNade = 0;
int cheat::updatedAmmo = 20;
int initialHealth = 0;
int initialNade = 0;
int initialAmmo = 0;
bool cheat::isNoRecoilOn = false; // check 
bool cheat::isInfNadeOn = false;
bool cheat::isInfAmmoOn = false;
bool cheat::isGodModeOn = false;  
bool cheat::isGetInfoOn = false;
bool cheat::isInfHealthOn = false;
std::uintptr_t cheat::headPtr = 0;
std::uintptr_t cheat::entityL = 0;
std::uintptr_t cheat::entity = 0;
float cheat::headValue = 0.0f;

void cheat::godmodeon() noexcept
{
    if (isGodModeOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto healthAddress = localPlayerPtr + m_iHealth;

    initialHealth = memory.Read<int>(healthAddress);

    isGodModeOn = true;

    while (isGodModeOn) {
        int currentHealth = memory.Read<int>(healthAddress);

        if (currentHealth < 9999) {
            memory.Write<int>(healthAddress, 100);
        }
        Sleep(10000000);
}


void cheat::godmodeoff() noexcept;
{
    if (!isGodModeOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto healthAddress = localPlayerPtr + m_iHealth;

    isGodModeOn = false;

    memory.Write<int>(healthAddress, initialHealth);
}

void cheat::infhealthon() noexcept
{
    if (isInfHealthOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto healthAddress = localPlayerPtr + m_iHealth;

    initialHealth = memory.Read<int>(healthAddress);

    isInfHealthOn = true;

    while (isInfHealthOn) {
        int currentHealth = memory.Read<int>(healthAddress);

        if (currentHealth < 9999) {
            memory.Write<int>(healthAddress, 100);
        }
        Sleep(100);
    }
}

void cheat::infhealthoff() noexcept
{
    if (!isInfHealthOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto healthAddress = localPlayerPtr + m_iHealth;

    isInfHealthOn = false;

    memory.Write<int>(healthAddress, initialHealth);
}

void cheat::infnadeon() noexcept 
{
    
}

void cheat::infnadeoff() noexcept
{
    
}

void cheat::infammoon() noexcept
{
    
}

void cheat::infammooff() noexcept
{
    
}

void cheat::norecoilon() noexcept 
{
    
}

void cheat::norecoiloff() noexcept 
{
    
}


void cheat::getinfoon() noexcept {
    
}


