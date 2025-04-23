#pragma once
#include <Windows.h>
#include <vector>

namespace offsets
{
	std::vector<uintptr_t> Settings = { 0x7EF0EB8, 0x10 };
	std::vector<uintptr_t> CPlayer = { 0x5E07850, 0x0, 0x28, 0x0, 0xE0, 0xA8, 0x110 };
	std::vector<uintptr_t> WeaponComponent = { 0x5E32C50, 0x88, 0x0, 0x30, 0x21, 0x70 };
	std::vector<uintptr_t> CCurrentWeapon2 = { 0x5E32C50, 0x88, 0x0, 0x30, 0x21, 0x70, 0x108, 0x0 };
	std::vector<uintptr_t> CCurrentWeapon3 = { 0x5E32C50, 0x88, 0x0, 0x30, 0x21, 0x70, 0x108, 0x0, 0x150, 0x0 };
	std::vector<uintptr_t> CCurrentWeapon4 = { 0x5E32C50, 0x88, 0x0, 0x30, 0x21, 0x70, 0x108, 0x0, 0x148, 0x0 };
	std::vector<uintptr_t> CCurrentWeapon5 = { 0x5E32C50, 0x88, 0x0, 0x30, 0x21, 0x70, 0x108, 0x0, 0x158, 0x0 };
	std::vector<uintptr_t> ESP = { 0x5E22F50, 0x48, 0x0 };
}

// Created with ReClass.NET 1.2 by KN4CK3R

class R6GamerProfileManager
{
public:
	char pad_0008[128]; //0x0008
	class Intermediate1* pIntermediate1; //0x0088
	char pad_0090[4016]; //0x0090
}; //Size: 0x1040

class R6SettingsBase
{
public:
	char pad_0000[16]; //0x0000
	class Settings* pSettings; //0x0010
	char pad_0018[4136]; //0x0018
}; //Size: 0x1040

class Settings
{
public:
	char pad_0000[3000]; //0x0000
	float PlayerFOV; //0x0BB8
	float GunFOV; //0x0BBC
	char pad_0BC0[1096]; //0x0BC0
}; //Size: 0x1008

class PlayerCameraManager
{
public:
	char pad_0000[112]; //0x0000
	class WeaponComponent* pIntermediate5; //0x0070
	char pad_0078[1936]; //0x0078
}; //Size: 0x0808

class WeaponComponent
{
public:
	char pad_0000[264]; //0x0000
	class Intermediate6* pIntermediate6; //0x0108
	char pad_0110[16]; //0x0110
	int8_t gunFireMode; //0x0120
	char pad_0121[3]; //0x0121
	int32_t gunAmmo; //0x0124
	char pad_0128[3811]; //0x0128
}; //Size: 0x100B

class CCurrentWeapon2
{
public:
	char pad_0000[240]; //0x0000
	uint64_t gunSound; //0x00F0
	char pad_00F8[72]; //0x00F8
	uint64_t pGunRecoil; //0x0140
	class Intermediate10* pIntermediate10; //0x0148
	class Intermediate8* pIntermediate8; //0x0150
	class Intermediate17* pIntermediate17; //0x0158
	char pad_0160[3784]; //0x0160
}; //Size: 0x1028

class CCurrentWeapon3
{
public:
	char pad_0000[60]; //0x0000
	int32_t GunFireRate; //0x003C
	char pad_0040[968]; //0x0040
}; //Size: 0x0408

class CCurrentWeapon4
{
public:
	char pad_0000[108]; //0x0000
	int32_t GunDamage; //0x006C
	char pad_0070[1944]; //0x0070
}; //Size: 0x0808

class CPlayer
{
public:
	char pad_0000[88]; //0x0000
	int32_t PlayerSpeed; //0x0058
	char pad_005C[4012]; //0x005C
}; //Size: 0x1008

class CCurrentWeapon5
{
public:
	char pad_0000[32]; //0x0000
	float GunSpread; //0x0020
	char pad_0024[996]; //0x0024
}; //Size: 0x0408

class ESP
{
public:
	char pad_0000[276]; //0x0000
	float espOutlineThickness; //0x0114
}; //Size: 0x0118