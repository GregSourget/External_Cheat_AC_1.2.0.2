#pragma once

#include <stdint.h>

// Joueur
constexpr auto localPlayer = 0x109B74;
constexpr auto entityList = 0x10F4F8;

constexpr auto m_iHealth = 0x0000F8;
constexpr auto m_iName = 0x205;
constexpr auto m_Armor = 0xFC;
constexpr auto m_XCoord = 0x28;
constexpr auto m_YCoord = 0x2C;
constexpr auto m_ZCoord = 0x30;
constexpr auto m_ViewangleWidth = 0x34;
constexpr auto m_ViewAngleHeight = 0x38;
constexpr auto m_iShotAmount = 0x180;
constexpr auto m_Kills = 0x1FC;
constexpr auto m_team = 0x32C;

constexpr auto m_vecOrigin = 0x28;
constexpr auto vec3_head = 0x4;
constexpr auto iTeamNum = 0x30C;
constexpr auto dwViewMatrix = 0x501AE8;

// weapon
constexpr auto m_Nades = 0x158;
constexpr auto m_Ammo = 0x150;
constexpr auto m_AmmoPistol = 0x13C;
constexpr auto m_recoil1 = 0x463786;
constexpr auto m_recoil2 = 0x46378E;

// recoil  4 63786
// 4 6378E

// Hacks
constexpr auto rapidFire = 0x164;


