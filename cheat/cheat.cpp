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
float cheat::updatedYaw = 0;
float cheat::updatedPitch = 0;
int initialHealth = 0;
int initialNade = 0;
int initialAmmo = 0;
int initialAmmoPistol = 0;
int initialArmor = 0;
int initialSpeed = 0;
int initialFire = 0;
float initialYaw = 0;
float initialPitch = 0;
bool cheat::isArmorOn = false;
bool cheat::isNoRecoilOn = false; // check 
bool cheat::isInfNadeOn = false;
bool cheat::isInfAmmoOn = false;
bool cheat::isGodModeOn = false;
bool cheat::isGetInfoOn = false;
bool cheat::isSpeedHackOn = false;
bool cheat::isRapidFireOn = false;
bool cheat::Isaimboton = false;
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


void cheat::getinfoon() noexcept {

}


void cheat::speedhackon() noexcept {
    if (isSpeedHackOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto speedhackAddress = localPlayerPtr + m_SpeedPlayer;

    initialSpeed = memory.Read<int>(speedhackAddress);

    isSpeedHackOn = true;

    int updatedSpeed = 5;
    memory.Write<int>(speedhackAddress, speedhackAddress*2);

}

void cheat::speedhackoff() noexcept {
    if (!isSpeedHackOn)
        return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    const auto speedhackAddress = localPlayerPtr + m_SpeedPlayer;

    isSpeedHackOn = false;

    memory.Write<int>(speedhackAddress, initialSpeed);
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



void cheat::aimboton() noexcept {
	if (Isaimboton)
		return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    const auto yAddress = entityListPtr + yaw;
	const auto xAddress = entityListPtr + pitch;
    

    std::cout << "yaw address:" << yAddress << std::endl;
	std::cout << "pitch address: " << xAddress << std::endl;
    initialYaw = memory.Read<float>(static_cast<std::uintptr_t>(yAddress));
    initialPitch = memory.Read<float>(static_cast<std::uintptr_t>(xAddress));
    


    Isaimboton = true;

    float updatedYaw = 200;
	float updatedPitch = 90;
    memory.Write<float>(static_cast<std::uintptr_t>(yAddress), updatedYaw);
    memory.Write<float>(static_cast<std::uintptr_t>(xAddress), updatedPitch);

}
/*
void cheat::aimboton() noexcept {
    if (Isaimboton)
        return;

    auto& memory = getMemory();

    // Étape 1 : Récupérer l'adresse du module
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) {
        std::cerr << "[Erreur] Impossible de récupérer l'adresse du module ac_client.exe" << std::endl;
        return;
    }
    std::cout << "[Info] Adresse de base du module : " << std::hex << moduleBase << std::endl;

    // Étape 2 : Lire l'adresse de la liste des entités
    const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
    if (entityListPtr == 0) {
        std::cerr << "[Erreur] Impossible de lire entityListPtr." << std::endl;
        return;
    }
    std::cout << "[Info] Adresse de entityListPtr : " << std::hex << entityListPtr << std::endl;

    // Étape 3 : Calculer les adresses yaw et pitch
    const auto yAddress = entityListPtr + yaw;
    const auto xAddress = entityListPtr + pitch;
    std::cout << "[Info] Adresse yaw : " << std::hex << yAddress << std::endl;
    std::cout << "[Info] Adresse pitch : " << std::hex << xAddress << std::endl;

    // Étape 4 : Lire les valeurs initiales
    initialYaw = memory.Read<float>(static_cast<std::uintptr_t>(yAddress));
    initialPitch = memory.Read<float>(static_cast<std::uintptr_t>(xAddress));
    if (initialYaw == 0.0f && initialPitch == 0.0f) {
        std::cerr << "[Avertissement] Les valeurs initiales yaw et pitch sont nulles." << std::endl;
    }
    std::cout << "[Info] Valeur initiale yaw : " << initialYaw << std::endl;
    std::cout << "[Info] Valeur initiale pitch : " << initialPitch << std::endl;

    // Indique que l'aimbot est actif
    Isaimboton = true;

    // Étape 5 : Écrire les nouvelles valeurs
    float updatedYaw = 200.0f;
    float updatedPitch = 90.0f;

    if (memory.Write<float>(static_cast<std::uintptr_t>(yAddress), updatedYaw), false) {
        std::cerr << "[Erreur] Échec de l'écriture de updatedYaw." << std::endl;
        return;
    }
    if (memory.Write<float>(static_cast<std::uintptr_t>(xAddress), updatedPitch), false) {
        std::cerr << "[Erreur] Échec de l'écriture de updatedPitch." << std::endl;
        return;
    }


    std::cout << "[Succès] Nouvelles valeurs écrites : Yaw = " << updatedYaw << ", Pitch = " << updatedPitch << std::endl;
}*/


void cheat::aimbotoff() noexcept {
	if (!Isaimboton)
		return;
}