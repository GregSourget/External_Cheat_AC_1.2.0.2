#pragma once

#include <stdint.h>


// Lists
constexpr auto localPlayer = 0x109B74;
constexpr auto entityList = 0x10F4F8;

constexpr auto m_iHealth = 0x0000F8;
constexpr auto m_iName = 0x205;
constexpr auto m_Armor = 0xFC;
//constexpr auto m_XCoord = 0x28;
//constexpr auto m_YCoord = 0x3C;
//constexpr auto m_ZCoord = 0x30;
constexpr auto m_ViewangleWidth = 0x34;
constexpr auto m_ViewAngleHeight = 0x38;
constexpr auto m_iShotAmount = 0x180;
constexpr auto m_SpeedPlayer = 0x80;
constexpr auto m_isPosMoving = 0x70;
constexpr auto m_iTeam = 0x10; //a verifier

constexpr auto m_vecOrigin = 0x28;
constexpr auto vec3_head = 0x4;
constexpr auto iTeamNum = 0x30C;
constexpr auto dwViewMatrix = 0x501AE8;
// ammo nade function recoil
constexpr auto m_Nades = 0x158;
constexpr auto m_Ammo = 0x150;
constexpr auto m_AmmoPistol = 0x13C;
constexpr auto m_recoil1 = 0x63786;
constexpr auto rapidFire = 0x4637E4;

// changer le nom des ennemies
constexpr auto m_name = 0x224;

//aimbot offset
constexpr auto headPos = 0x04;
constexpr auto footPos = 0x34;
constexpr float yaw = 0x40;
constexpr float pitch = 0x44;
constexpr auto team = 0x032C;