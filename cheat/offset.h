#pragma once

#include <stdint.h>

// Bases
constexpr auto localPlayer = 0x109B74;
constexpr auto entityList = 0x10F4F8;
constexpr auto off_nb_entities = 0x10F500;


//Player
constexpr auto m_iHealth = 0x0000F8;
constexpr auto m_iName = 0x205;
constexpr auto m_Armor = 0xFC;

constexpr auto headX = 0x4;
constexpr auto headY = 0x8;
constexpr auto headZ = 0xC;

constexpr auto feetX = 0x28;
constexpr auto feetY = 0x2C;
constexpr auto feetZ = 0x30;

constexpr auto m_ViewangleWidth = 0x34;
constexpr auto m_ViewAngleHeight = 0x38;
constexpr auto m_yaw = 0x40;
constexpr auto m_pitch = 0x44;
constexpr auto m_iShotAmount = 0x180;


constexpr auto m_vecOrigin = 0x28;
//constexpr auto vec3_head = 0x4;
constexpr auto iTeamNum = 0x32C;
constexpr auto dwViewMatrix = 0x501AE8;
//ptr view matrix 17F00
// ammo nade function recoil
constexpr auto m_Nades = 0x158;
constexpr auto m_Ammo = 0x150;
constexpr auto m_AmmoPistol = 0x13C;
constexpr auto m_recoil1 = 0x0005BAAD;



//recoil ac_client.exe+63786 - 50                    - push eax
//ac_client.exe + 63787 - 8D 4C 24 1C - lea ecx, [esp + 1C]
//ac_client.exe + 6378B - 51 - push ecx
//ac_client.exe + 6378C - 8B CE - mov ecx, esi
//ac_client.exe + 6378E - FF D2 - call edx
//entitylist + 4 pour un joueur



// Hacks
constexpr auto rapidFire = 0x164;

