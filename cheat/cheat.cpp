#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"
#include <thread>


int cheat::updatedHealth = 100; //initalisation
int cheat::updatedNade = 0;
int cheat::updatedAmmo = 20;
int cheat::updatedArmor = 0;
int cheat::updatedFire = 0;
int cheat::updatedRecoil = 0;
//int cheat::updatedFly = 0;
int initialHealth = 0;
int initialNade = 0;
int initialAmmo = 0;
int initialArmor = 0;
int initialFire = 0;
int initialRecoil = 0;
//int initialFly = 0;
bool cheat::isArmorOn = false;
bool cheat::isNoRecoilOn = false; // check 
bool cheat::isInfNadeOn = false;
bool cheat::isInfAmmoOn = false;
bool cheat::isGodModeOn = false;
bool cheat::isGetInfoOn = false;
bool cheat::isRapidFireOn = false;
//bool cheat::isFlyOn = false;
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

    int updatedHealth = 10000;
    memory.Write<int>(healthAddress, updatedHealth);

    std::thread([healthAddress, &memory]() {
        while (cheat::isGodModeOn) {
            int currentHealth = memory.Read<int>(healthAddress);
            if (currentHealth < 10000) {
                memory.Write<int>(healthAddress, 10000);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        }).detach();
}


void cheat::godmodeoff() noexcept
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

void cheat::infnadeon() noexcept
{
    if (isInfNadeOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto nadeAddress = localPlayerPtr + fly;

    initialNade = memory.Read<int>(nadeAddress);

    isInfNadeOn = true;

    int updatedNade = -300;
    memory.Write<int>(nadeAddress, updatedNade);

    std::thread([nadeAddress, &memory]() {
        while (cheat::isInfNadeOn) {
            int currentNade = memory.Read<int>(nadeAddress);
            if (currentNade > -250) {
                memory.Write<int>(nadeAddress, -300);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        }).detach();
}


void cheat::infnadeoff() noexcept
{
    if (!isInfNadeOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto nadeAddress = localPlayerPtr + m_Nades;

    isInfNadeOn = false;

    memory.Write<int>(nadeAddress, initialNade);

}

void cheat::infammoon() noexcept
{
    if (isInfAmmoOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto ammoAddress = localPlayerPtr + m_Ammo;

    initialAmmo = memory.Read<int>(ammoAddress);

    isInfAmmoOn = true;

    int updatedAmmo = 20;
    memory.Write<int>(ammoAddress, updatedAmmo);

    std::thread([ammoAddress, &memory]() {
        while (cheat::isInfAmmoOn) {
            int currentAmmo = memory.Read<int>(ammoAddress);
            if (currentAmmo < 20) {
                memory.Write<int>(ammoAddress, 20);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::infammooff() noexcept
{
    if (!isInfAmmoOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto ammoAddress = localPlayerPtr + m_Ammo;

    isInfAmmoOn = false;

    memory.Write<int>(ammoAddress, initialAmmo);
}



void cheat::norecoilon() noexcept
{
    if (isNoRecoilOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto baseAddressPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    const auto recoilAddress = m_recoil1;

    initialRecoil = memory.Read<int>(recoilAddress);
    std::cout << "Initial Recoil: " << initialRecoil << std::endl;

    isNoRecoilOn = true;

    int updatedRecoil = 9816684;
    memory.Write<int>(recoilAddress, updatedRecoil);

    std::thread([recoilAddress, &memory]() {
        while (cheat::isNoRecoilOn) {
            int currentRecoil = memory.Read<int>(recoilAddress);
            if (currentRecoil > 0) {
                memory.Write<int>(recoilAddress, 0);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        }).detach();

}

void cheat::norecoiloff() noexcept
{
    if (!isNoRecoilOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    const auto recoilAddress = entityListPtr + m_recoil1;

    isNoRecoilOn = false;

    memory.Write<int>(recoilAddress, initialRecoil);
}


void cheat::armoron() noexcept {

    if (isArmorOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto armorAddress = localPlayerPtr + m_Armor;

    initialArmor = memory.Read<int>(armorAddress);

    isArmorOn = true;

    int updatedArmor = 250;
    memory.Write<int>(armorAddress, updatedArmor);
    std::thread([armorAddress, &memory]() {
        while (cheat::isArmorOn) {
            int currentArmor = memory.Read<int>(armorAddress);
            if (currentArmor < 250) {
                memory.Write<int>(armorAddress, 250);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        }).detach();
}
void cheat::armoroff() noexcept {
    if (!isArmorOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto armorAddress = localPlayerPtr + m_Armor;

    isArmorOn = false;

    memory.Write<int>(armorAddress, initialArmor);

}


void cheat::getinfoon() noexcept {

}


void cheat::rapidfireon() noexcept {

    if (isRapidFireOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    const auto fireAddress = entityListPtr + rapidFire;

    initialFire = memory.Read<int>(fireAddress);

    isRapidFireOn = true;

    int updatedFire = 1988823685;
    memory.Write<int>(fireAddress, updatedFire);
}


void cheat::rapidfireoff() noexcept {

    if (!isRapidFireOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    const auto fireAddress = entityListPtr + rapidFire;

    isRapidFireOn = false;

    memory.Write<int>(fireAddress, initialFire);
}


//void cheat::flyon() noexcept {
//
//	if (isFlyOn)
//		return;
//
//	auto& memory = getMemory();
//	const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
//	const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
//	const auto flyAddress = localPlayer + fly;
//
//
//}