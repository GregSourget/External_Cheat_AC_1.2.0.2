//#include <Windows.h>
#include <vector>
#include <iostream>
//#include <CommCtrl.h>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"
#include "struct.h"
#include "entities.h"
#include <thread>

int cheat::updatedHealth = 100; //initalisation
int cheat::updatedNade = 0;
int cheat::updatedAmmo = 20;
int cheat::updatedArmor = 0;
int initialHealth = 0;
int initialNade = 0;
int initialAmmo = 0;
int initialAmmoPistol = 0;
int initialArmor = 0;
bool cheat::isArmorOn = false;
bool cheat::isNoRecoilOn = false; // check 
bool cheat::isInfNadeOn = false;
bool cheat::isInfAmmoOn = false;
bool cheat::isGodModeOn = false;
//bool cheat::isGetInfoOn = false;
//bool cheat::isESPOn = false;
bool cheat::isAimBotOn = false;
//std::uintptr_t cheat::headPtr = 0;
//std::uintptr_t cheat::entityL = 0;
//std::uintptr_t cheat::entity = 0;
//float cheat::headValue = 0.0f;

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
    const auto nadeAddress = localPlayerPtr + m_Nades;

    initialNade = memory.Read<int>(nadeAddress);

    isInfNadeOn = true;

    int updatedNade = 1;
    memory.Write<int>(nadeAddress, updatedNade);

    // Create a thread to monitor the nade count
    std::thread([nadeAddress, &memory]() {
        while (cheat::isInfNadeOn) {
            int currentNade = memory.Read<int>(nadeAddress);
            if (currentNade == 0) {
                memory.Write<int>(nadeAddress, 1);   
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
    const auto pistolAmmoAddress = localPlayerPtr + m_AmmoPistol;

    initialAmmo = memory.Read<int>(ammoAddress);
    initialAmmoPistol = memory.Read<int>(pistolAmmoAddress);

    isInfAmmoOn = true;

    int updatedAmmo = 100;
    memory.Write<int>(ammoAddress, updatedAmmo);
    memory.Write<int>(pistolAmmoAddress, updatedAmmo);

    std::thread([ammoAddress, pistolAmmoAddress, &memory]() {
        while (cheat::isInfAmmoOn) {
            int currentAmmo = memory.Read<int>(ammoAddress);
            int currentPistolAmmo = memory.Read<int>(pistolAmmoAddress);
            if (currentAmmo < 100) {
                memory.Write<int>(ammoAddress, 100);
            }
            if (currentPistolAmmo < 100) {
                memory.Write<int>(pistolAmmoAddress, 100);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
    const auto pistolAmmoAddress = localPlayerPtr + m_AmmoPistol;

    isInfAmmoOn = false;

    memory.Write<int>(ammoAddress, initialAmmo);
    memory.Write<int>(pistolAmmoAddress, initialAmmoPistol);
}


void cheat::norecoilon() noexcept
{

}

void cheat::norecoiloff() noexcept
{

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


//void cheat::getinfoon() noexcept {
//
//}


void cheat::aimboton() noexcept {

    //rajouter le fait qu'on puisse l'activer avec une touche
    //rajouter le fait que ca lock sur l'ennemi que si il est visible ou alors que ca tire a travers les murs a voir
    if (isAimBotOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto yawAddress = localPlayerPtr + m_yaw;
    const auto pitchAddress = localPlayerPtr + m_pitch;

    isAimBotOn = true;

    std::thread([yawAddress, pitchAddress, &memory]() {
        while (cheat::isAimBotOn) {
            std::vector<Entity> entities = GetEntitiesInfo();
            Entity Player = entities[0];
            Vector3 headPlayer = Player.headPosition;

            Vector3 headEnemy = GetClosestEnemyPos();

            //if there are no enemies alive, pause the aimbot
            if (headEnemy.x == 0 && headEnemy.y == 0 && headEnemy.z == 0) {
                continue;
            }
            float deltaX = headEnemy.x - headPlayer.x;
            float deltaY = headEnemy.y - headPlayer.y;
            float deltaZ = headEnemy.z - headPlayer.z;

            float horizontalDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
            float pitch = std::atan2(deltaZ, horizontalDistance) * 180.0f / 3.14159f;
            float yaw = std::atan2(deltaY, deltaX) * 180.0f / 3.14159f;
            yaw = yaw + 90;

            memory.Write<float>(yawAddress, yaw);
            memory.Write<float>(pitchAddress, pitch);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::aimbotoff() noexcept {
    if (!isAimBotOn)
        return;
    isAimBotOn = false;
}