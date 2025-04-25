#pragma once
#include <iostream>
#include <cstdint>
#include <thread>
#include "offsets.h"
#include <Psapi.h>
#include <vector>
#include <TlHelp32.h>
#include <winternl.h>

// ANSI codes
// Standard colors
const std::string RESET = "\033[0m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

// Bright colors
const std::string BRIGHT_BLACK = "\033[90m";
const std::string BRIGHT_RED = "\033[91m";
const std::string BRIGHT_GREEN = "\033[92m";
const std::string BRIGHT_YELLOW = "\033[93m";
const std::string BRIGHT_BLUE = "\033[94m";
const std::string BRIGHT_MAGENTA = "\033[95m";
const std::string BRIGHT_CYAN = "\033[96m";
const std::string BRIGHT_WHITE = "\033[97m";

// Backgrounds (standard)
const std::string BG_BLACK = "\033[40m";
const std::string BG_RED = "\033[41m";
const std::string BG_GREEN = "\033[42m";
const std::string BG_YELLOW = "\033[43m";
const std::string BG_BLUE = "\033[44m";
const std::string BG_MAGENTA = "\033[45m";
const std::string BG_CYAN = "\033[46m";
const std::string BG_WHITE = "\033[47m";

// Backgrounds (bright)
const std::string BG_BRIGHT_BLACK = "\033[100m";
const std::string BG_BRIGHT_RED = "\033[101m";
const std::string BG_BRIGHT_GREEN = "\033[102m";
const std::string BG_BRIGHT_YELLOW = "\033[103m";
const std::string BG_BRIGHT_BLUE = "\033[104m";
const std::string BG_BRIGHT_MAGENTA = "\033[105m";
const std::string BG_BRIGHT_CYAN = "\033[106m";
const std::string BG_BRIGHT_WHITE = "\033[107m";

// Text effects
const std::string BOLD = "\033[1m";
const std::string UNDERLINE = "\033[4m";
const std::string BLINK = "\033[5m";
const std::string INVERT = "\033[7m";
const std::string HIDDEN = "\033[8m";

// 256-color mode (text)
const std::string ORANGE_256 = "\033[38;5;208m";
const std::string PINK_256 = "\033[38;5;200m";
const std::string TEAL_256 = "\033[38;5;37m";
const std::string GREY_256 = "\033[38;5;244m";
const std::string PURPLE_256 = "\033[38;5;129m";
const std::string NEON_GREEN_256 = "\033[38;5;118m";
const std::string SKY_BLUE_256 = "\033[38;5;75m";

// RGB True Color (foreground)
const std::string RGB_PURPLE = "\033[38;2;204;153;255m";
const std::string RGB_PINK = "\033[38;2;255;105;180m";
const std::string RGB_ORANGE = "\033[38;2;255;165;0m";
const std::string RGB_SKY = "\033[38;2;135;206;250m";
const std::string RGB_AQUA = "\033[38;2;0;255;255m";
const std::string RGB_LIME = "\033[38;2;50;205;50m";
const std::string RGB_GOLD = "\033[38;2;255;215;0m";
const std::string RGB_CORAL = "\033[38;2;255;127;80m";
const std::string RGB_INDIGO = "\033[38;2;75;0;130m";
const std::string RGB_MINT = "\033[38;2;152;255;152m";

extern uintptr_t baseAddress;
extern CCurrentWeapon2* currentWeapon2;
extern CCurrentWeapon3* currentWeapon3;
extern CCurrentWeapon4* currentWeapon4;
extern CCurrentWeapon5* currentWeapon5;
extern CPlayer* player;
extern Settings* settings;
extern WeaponComponent* weaponComponent;

extern bool noRecoilEnabled;
extern bool fireRateEnabled;
extern bool infiniteAmmoEnabled;
extern bool powerfulAmmoEnabled;
extern bool noSpreadEnabled;
extern bool movementSpeedEnabled;
extern bool fishEyeEnabled;
extern bool glowEspEnabled;
extern bool runShootEnabled;
extern bool boltScriptEnabled;
extern bool infiniteGadgetEnabled;
extern bool goOutsideEnabled;
extern bool skyBoxEnabled;
extern int gunCaliberIndex;
int64_t originalRecoilValue;
int64_t originalGunSoundValue;
int32_t originalFirerateValue;
int32_t originalAmmoValue;
int32_t originalGunDamageValue;
int32_t originalGunWallDamageValue;
int32_t originalPlayerSpeedValue;
int8_t originalFireModeValue;
float originalGunSpreadValue;
float originalPlayerFovValue;
float originalGunFovValue;

uint32_t gunCaliberModes[] = {
	3864566559, // Regular Rifle
	// 224916230// Regular Pistol
	//1635385480// Regular SMG
	1216095593, // Skeleton Key
	3683118896, // Kali’s Sniper
	2249646560, // Tachanka’s DP27
	// 54247478 // Tachanka's DP27 (stationary turret) 
	2097060903  // Maverick’s Blowtorch
};

void MsgBoxAddy(uintptr_t addy)
{
	char szAddressOnly[32];
	sprintf_s(szAddressOnly, "%016llX", addy);

	const size_t len = strlen(szAddressOnly) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	if (hMem)
	{
		void* pMem = GlobalLock(hMem);
		if (pMem)  // Check if GlobalLock succeeded
		{
			memcpy(pMem, szAddressOnly, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
		}
		else
		{
			// Handle error: GlobalLock failed
			MessageBoxA(NULL, "Failed to lock global memory.", "Error", MB_OK);
		}
	}
	else
	{
		// Handle error: GlobalAlloc failed
		MessageBoxA(NULL, "Failed to allocate global memory.", "Error", MB_OK);
	}

	char szFullMsg[64];
	sprintf_s(szFullMsg, "Address copied: %s", szAddressOnly);
	MessageBoxA(NULL, szFullMsg, "Copied!", MB_OK);
}

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modInfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modInfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
	return modInfo;
}

void WriteToMemory(HANDLE hProcess, uintptr_t addressToWrite, char* valueToWrite, int cb)
{
	DWORD flOldProtect = NULL;

	if (VirtualProtectEx(hProcess, (LPVOID)addressToWrite, cb, PAGE_EXECUTE_READWRITE, &flOldProtect))
	{
		memcpy((void*)addressToWrite, valueToWrite, cb);
		VirtualProtectEx(hProcess, (LPVOID)addressToWrite, cb, flOldProtect, &flOldProtect);    // This needs to be VirtualProtectEx too!
	}
	else
	{
		CHAR szErrorBuffer[256];
		FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr,
			GetLastError(),
			LANG_ENGLISH,
			szErrorBuffer,
			sizeof(szErrorBuffer),
			nullptr
		);

		std::cout << "VPEX failed: " << szErrorBuffer << '\n';
	}
}

void debug(uintptr_t addy)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)addy, &mbi, sizeof(mbi));
	char regionMsg[256];
	sprintf_s(regionMsg, "Before Patch:\nProtect: 0x%X\nState: 0x%X\nType: 0x%X", mbi.Protect, mbi.State, mbi.Type);
	MessageBoxA(0, regionMsg, "Memory Info", 0);
}

uintptr_t FindPattern(const char* module, const char* pattern, const char* mask)
{
	MODULEINFO moduleInfo = GetModuleInfo(module);
	uintptr_t baseAddress = (uintptr_t)moduleInfo.lpBaseOfDll;
	uintptr_t moduleSize = (uintptr_t)moduleInfo.SizeOfImage;
	uintptr_t patternLength = (uintptr_t)strlen(mask);
	for (uintptr_t i = 0; i < moduleSize - patternLength; i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || pattern[j] == *(char*)(baseAddress + i + j);
		}
		if (found)
		{
			return baseAddress + i;
		}
	}
	return NULL;
}

void showMenuInit()
{
	std::cout << RGB_PURPLE + BOLD << R"(
+-----------------------------------------+
|     /\___/\                             |
|    ( o   o )   Injected!                |
|    (  =^=  )                            |
|    (        )                           |
|    (         )   Read that warning.     |
|    (          )))))))))))))))           |
+-----------------------------------------+
)" << RESET << "\n";

	std::cout << BOLD + RGB_PURPLE + "Internal" + RESET << "\n";
	std::cout << "[1] [" << RED + "OFF" + RESET << "] Infinite Ammo\n";
	std::cout << "[2] [" << RED + "OFF" + RESET << "] Rapid Fire*\n";
	std::cout << "[3] [" << RED + "OFF" + RESET << "] No Recoil*\n";
	std::cout << "[4] [" << RED + "OFF" + RESET << "] No Spread*\n";
	std::cout << "[5] [" << RED + "OFF" + RESET << "] Instant Kill*\n";
	std::cout << "[6] [" << RED + "OFF" + RESET << "] Speedy Gonzales*\n";
	std::cout << "[7] [" << RED + "OFF" + RESET << "] Fisheye FOV\n";
	std::cout << "[8] [" << RED + "OFF" + RESET << "] Remove Sky\n";
	std::cout << "[9] [" << RED + "OFF" + RESET << "] Gun Caliber*\n\n";
	std::cout << BOLD + RGB_PURPLE + "External" + RESET << "\n";
	std::cout << "[F1] [" << RED + "OFF" + RESET << "] Glow ESP\n";
	std::cout << "[F2] [" << RED + "OFF" + RESET << "] Run and Shoot\n";
	std::cout << "[F3] [" << RED + "OFF" + RESET << "] Remove Pump Action / Bolt Action\n";
	std::cout << "[F4] [" << RED + "OFF" + RESET << "] Infinite Gadgets\n";
	std::cout << "[F5] [" << RED + "OFF" + RESET << "] Can Go Outside \n";
	std::cout << "\n" + BOLD + BRIGHT_RED +
		"Warning: The game may crash if features marked with a * are left enabled while leaving or joining sessions.\n" + RESET;
}

void showMenu(bool noRecoil, bool fireRate, bool infiniteAmmo, bool powerfulAmmo, bool noSpread, bool movementSpeed, bool fishEye, bool glowEsp, bool runShoot, bool boltScript, bool skybox, bool infGadget, bool goOutside, int caliber)
{
	std::string caliberToggle;
	std::string caliberText;
	switch (caliber)
	{
	case 0:
		caliberToggle = "[" + RED + "OFF" + RESET + "]";
		caliberText = "";
		break;
	case 1:
		caliberToggle = "[" + GREEN + "ON" + RESET + "]";
		caliberText = "[" + ORANGE_256 + "Skeleton Key" + RESET + "]";
		break;
	case 2:
		caliberToggle = "[" + GREEN + "ON" + RESET + "]";
		caliberText = "[" + BRIGHT_YELLOW + "CSRX 300" + RESET + "]";
		break;
	case 3:
		caliberToggle = "[" + GREEN + "ON" + RESET + "]";
		caliberText = "[" + NEON_GREEN_256 + "DP27" + RESET + "]";
		break;
	case 4:
		caliberToggle = "[" + GREEN + "ON" + RESET + "]";
		caliberText = "[" + SKY_BLUE_256 + "Mav Blowtorch" + RESET + "]";
		break;
	default:
		caliberToggle = "[" + GREEN + "ON" + RESET + "]";
		caliberText = RED + "[Unknown]" + RESET;
		break;
	}

	std::cout << RGB_PURPLE + BOLD << R"(
+-----------------------------------------+
|     /\___/\                             |
|    ( o   o )   Injected!                |
|    (  =^=  )                            |
|    (        )                           |
|    (         )   )" << BLINK + BRIGHT_RED + "[0] Uninject" + RESET + RGB_PURPLE + BOLD << R"(           |
|    (          )))))))))))))))           |
+-----------------------------------------+
)" << RESET << "\n";

	std::cout << BOLD + RGB_PURPLE + "Internal" + RESET << "\n";
	std::cout << "[1] [" << (infiniteAmmo ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Infinite Ammo\n";
	std::cout << "[2] [" << (fireRate ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Rapid Fire\n";
	std::cout << "[3] [" << (noRecoil ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] No Recoil\n";
	std::cout << "[4] [" << (noSpread ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] No Spread\n";
	std::cout << "[5] [" << (powerfulAmmo ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Instant Kill\n";
	std::cout << "[6] [" << (movementSpeed ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Speedy Gonzales\n";
	std::cout << "[7] [" << (fishEye ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Fisheye FOV\n";
	std::cout << "[8] [" << (skybox ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Remove Sky\n";
	std::cout << "[9] " << caliberToggle << " Gun Caliber " << caliberText << "\n\n";
	std::cout << BOLD + RGB_PURPLE + "External" + RESET << "\n";
	std::cout << "[F1] [" << (glowEsp ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Glow ESP\n";
	std::cout << "[F2] [" << (runShoot ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Run and Shoot\n";
	std::cout << "[F3] [" << (boltScript ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Remove Pump Action / Bolt Action\n";
	std::cout << "[F4] [" << (infGadget ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Infinite Gadgets\n";
	std::cout << "[F5] [" << (goOutside ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Can Go Outside\n\n";
}

void WaitForKeyRelease(int vkKey)
{
	while (GetAsyncKeyState(vkKey)) Sleep(10);
}

bool CanUninject(bool thread1Running, bool thread2Running, bool thread3Running, bool thread4Running, bool thread5Running, bool thread6Running, bool thread7Running, bool thread8Running)
{
	if (thread1Running || thread2Running || thread3Running || thread4Running || thread5Running || thread6Running || thread7Running || thread8Running)
		return false; // Returns false if a thread is still running
	else
		return true; // Returns true if all threads have exited
}

uintptr_t GetPointer(uintptr_t base, std::vector<uintptr_t> offsets)
{
	uintptr_t addr = base;
	for (size_t i = 0; i < offsets.size(); ++i)
	{
		if (!addr) return 0;
		addr = *reinterpret_cast<uintptr_t*>(addr + offsets[i]);
	}
	return addr;
}

void CallExternal(const char* exePath)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	if (!CreateProcessA(exePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		std::cerr << "CreateProcess failed. Error: " << GetLastError() << "\n";
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

void ToggleNoRecoil()
{
	noRecoilEnabled = !noRecoilEnabled;
	if (noRecoilEnabled)
	{
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon2);
		if (!weaponPtr || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon2)))
		{
			noRecoilEnabled = false;
			return;
		}

		CCurrentWeapon2* currentWeapon2 = reinterpret_cast<CCurrentWeapon2*>(weaponPtr);
		originalRecoilValue = currentWeapon2->pGunRecoil;
	}
	WaitForKeyRelease(VK_NUMPAD3);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainNoRecoil()
{
	ULONGLONG invalidStartTime = 0;

	while (noRecoilEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);

		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon2);
		bool valid = weaponPtr && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon2));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 4000)
			{
				noRecoilEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		CCurrentWeapon2* currentWeapon2 = reinterpret_cast<CCurrentWeapon2*>(weaponPtr);
		currentWeapon2->pGunRecoil = 0;

		if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
		{
			noRecoilEnabled = false;
			currentWeapon2->pGunRecoil = originalRecoilValue;
			WaitForKeyRelease(VK_NUMPAD3);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void ToggleFireRate()
{
	fireRateEnabled = !fireRateEnabled;
	if (fireRateEnabled)
	{
		uintptr_t weaponPtr1 = GetPointer(baseAddress, offsets::WeaponComponent);
		uintptr_t weaponPtr2 = GetPointer(baseAddress, offsets::CCurrentWeapon2);
		uintptr_t weaponPtr3 = GetPointer(baseAddress, offsets::CCurrentWeapon3);
		if (!weaponPtr1 || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr1), sizeof(WeaponComponent)) || !weaponPtr2 || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr2), sizeof(CCurrentWeapon2)) || !weaponPtr3 || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr3), sizeof(CCurrentWeapon3)))
		{
			fireRateEnabled = false;
			return;
		}

		WeaponComponent* currentWeapon1 = reinterpret_cast<WeaponComponent*>(weaponPtr1);
		CCurrentWeapon2* currentWeapon2 = reinterpret_cast<CCurrentWeapon2*>(weaponPtr2);
		CCurrentWeapon3* currentWeapon3 = reinterpret_cast<CCurrentWeapon3*>(weaponPtr3);
		originalFireModeValue = currentWeapon1->gunFireMode;
		originalGunSoundValue = currentWeapon2->gunSound;
		originalFirerateValue = currentWeapon3->GunFireRate;
	}
	WaitForKeyRelease(VK_NUMPAD2);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainFireRate()
{
	ULONGLONG invalidStartTime = 0;

	while (fireRateEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t weaponPtr1 = GetPointer(baseAddress, offsets::WeaponComponent);
		uintptr_t weaponPtr2 = GetPointer(baseAddress, offsets::CCurrentWeapon2);
		uintptr_t weaponPtr3 = GetPointer(baseAddress, offsets::CCurrentWeapon3);
		bool valid = weaponPtr1 && weaponPtr2 && weaponPtr3 && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr1), sizeof(WeaponComponent)) && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr2), sizeof(CCurrentWeapon2)) && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr3), sizeof(CCurrentWeapon3));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 3750)
			{
				fireRateEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		WeaponComponent* currentWeapon1 = reinterpret_cast<WeaponComponent*>(weaponPtr1);
		CCurrentWeapon2* currentWeapon2 = reinterpret_cast<CCurrentWeapon2*>(weaponPtr2);
		CCurrentWeapon3* currentWeapon3 = reinterpret_cast<CCurrentWeapon3*>(weaponPtr3);
		if (currentWeapon1->gunFireMode != 0)
			currentWeapon1->gunFireMode = 0;
		if (currentWeapon2->gunSound != 0)
			currentWeapon2->gunSound = 0;
		if (currentWeapon3->GunFireRate != 9999)
			currentWeapon3->GunFireRate = 9999;


		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		{
			fireRateEnabled = false;
			currentWeapon1->gunFireMode = originalFireModeValue;
			currentWeapon2->gunSound = originalGunSoundValue;
			currentWeapon3->GunFireRate = originalFirerateValue;
			WaitForKeyRelease(VK_NUMPAD2);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void ToggleInfiniteAmmo()
{
	infiniteAmmoEnabled = !infiniteAmmoEnabled;
	if (infiniteAmmoEnabled)
	{
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::WeaponComponent);
		if (!weaponPtr || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(WeaponComponent)))
		{
			infiniteAmmoEnabled = false;
			return;
		}

		WeaponComponent* weaponComponent = reinterpret_cast<WeaponComponent*>(weaponPtr);
		originalAmmoValue = weaponComponent->gunAmmo;
	}
	WaitForKeyRelease(VK_NUMPAD1);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainInfiniteAmmo()
{
	ULONGLONG invalidStartTime = 0;

	while (infiniteAmmoEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::WeaponComponent);
		bool valid = weaponPtr && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(WeaponComponent));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 1500)
			{
				infiniteAmmoEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		WeaponComponent* weaponComponent = reinterpret_cast<WeaponComponent*>(weaponPtr);
		weaponComponent->gunAmmo = 9999;


		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
		{
			infiniteAmmoEnabled = false;
			weaponComponent->gunAmmo = originalAmmoValue;
			WaitForKeyRelease(VK_NUMPAD1);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void TogglePowerfulAmmo()
{
	powerfulAmmoEnabled = !powerfulAmmoEnabled;
	if (powerfulAmmoEnabled)
	{
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon4);
		if (!weaponPtr || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon4)))
		{
			powerfulAmmoEnabled = false;
			return;
		}

		CCurrentWeapon4* currentWeapon4 = reinterpret_cast<CCurrentWeapon4*>(weaponPtr);
		originalGunDamageValue = currentWeapon4->GunDamage;
	}
	WaitForKeyRelease(VK_NUMPAD5);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainPowerfulAmmo()
{
	ULONGLONG invalidStartTime = 0;

	while (powerfulAmmoEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon4);
		bool valid = weaponPtr && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon4));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 5500)
			{
				powerfulAmmoEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		CCurrentWeapon4* currentWeapon4 = reinterpret_cast<CCurrentWeapon4*>(weaponPtr);
		currentWeapon4->GunDamage = 9999;


		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			powerfulAmmoEnabled = false;
			currentWeapon4->GunDamage = originalGunDamageValue;
			WaitForKeyRelease(VK_NUMPAD5);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void ToggleNoSpread()
{
	noSpreadEnabled = !noSpreadEnabled;
	if (noSpreadEnabled)
	{
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon5);
		if (!weaponPtr || IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon5)))
		{
			noSpreadEnabled = false;
			return;
		}

		CCurrentWeapon5* currentWeapon5 = reinterpret_cast<CCurrentWeapon5*>(weaponPtr);
		originalGunSpreadValue = currentWeapon5->GunSpread;
	}
	WaitForKeyRelease(VK_NUMPAD4);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainNoSpread()
{
	ULONGLONG invalidStartTime = 0;

	while (noSpreadEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t weaponPtr = GetPointer(baseAddress, offsets::CCurrentWeapon5);
		bool valid = weaponPtr && !IsBadReadPtr(reinterpret_cast<void*>(weaponPtr), sizeof(CCurrentWeapon5));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 5000)
			{
				noSpreadEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		CCurrentWeapon5* currentWeapon5 = reinterpret_cast<CCurrentWeapon5*>(weaponPtr);
		currentWeapon5->GunSpread = 0;


		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			noSpreadEnabled = false;
			currentWeapon5->GunSpread = originalGunSpreadValue;
			WaitForKeyRelease(VK_NUMPAD4);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void ToggleMovementSpeed()
{
	movementSpeedEnabled = !movementSpeedEnabled;
	if (movementSpeedEnabled)
	{
		uintptr_t playerPtr = GetPointer(baseAddress, offsets::CPlayer);
		if (!playerPtr || IsBadReadPtr(reinterpret_cast<void*>(playerPtr), sizeof(CPlayer)))
		{
			movementSpeedEnabled = false;
			return;
		}

		CPlayer* player = reinterpret_cast<CPlayer*>(playerPtr);
		originalPlayerSpeedValue = player->PlayerSpeed;
	}
	WaitForKeyRelease(VK_NUMPAD6);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainMovementSpeed()
{
	ULONGLONG invalidStartTime = 0;

	while (movementSpeedEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t playerPtr = GetPointer(baseAddress, offsets::CPlayer);
		bool valid = playerPtr && !IsBadReadPtr(reinterpret_cast<void*>(playerPtr), sizeof(CPlayer));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 6000)
			{
				movementSpeedEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		CPlayer* player = reinterpret_cast<CPlayer*>(playerPtr);
		player->PlayerSpeed = 250;


		if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		{
			movementSpeedEnabled = false;
			player->PlayerSpeed = originalPlayerSpeedValue;
			WaitForKeyRelease(VK_NUMPAD6);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void ToggleFishEye()
{
	fishEyeEnabled = !fishEyeEnabled;
	if (fishEyeEnabled)
	{
		uintptr_t settingsPtr = GetPointer(baseAddress, offsets::Settings);
		if (!settingsPtr || IsBadReadPtr(reinterpret_cast<void*>(settingsPtr), sizeof(Settings)))
		{
			fishEyeEnabled = false;
			return;
		}

		Settings* settings = reinterpret_cast<Settings*>(settingsPtr);
		originalPlayerFovValue = settings->PlayerFOV;
		originalGunFovValue = settings->GunFOV;
	}
	WaitForKeyRelease(VK_NUMPAD7);
	system("cls");
	showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
}

void MaintainFishEye()
{
	ULONGLONG invalidStartTime = 0;

	while (fishEyeEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t settingsPtr = GetPointer(baseAddress, offsets::Settings);
		bool valid = settingsPtr && !IsBadReadPtr(reinterpret_cast<void*>(settingsPtr), sizeof(Settings));

		if (!valid)
		{
			if (invalidStartTime == 0)
			{
				invalidStartTime = GetTickCount64(); // start the "invalid" timer
			}
			else if (GetTickCount64() - invalidStartTime >= 2000) // completely irrelevant as this memory region never becomes invalid, but I honestly can not be asked removing it.
			{
				fishEyeEnabled = false;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0; // reset timer if memory becomes valid again
		}

		Settings* settings = reinterpret_cast<Settings*>(settingsPtr);
		settings->PlayerFOV = 1.8;
		settings->GunFOV = 1.8;


		if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
		{
			fishEyeEnabled = false;
			settings->PlayerFOV = originalPlayerFovValue;
			settings->GunFOV = originalGunFovValue;
			WaitForKeyRelease(VK_NUMPAD7);
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
			break;
		}
	}
}

void HandleGunCaliber()
{
	ULONGLONG invalidStartTime = 0;

	while (!GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t caliberPtr = GetPointer(baseAddress, offsets::CCurrentWeaponCaliber);
		bool valid = caliberPtr && !IsBadReadPtr(reinterpret_cast<void*>(caliberPtr), sizeof(CCurrentWeaponCaliber));

		if (!valid)
		{
			if (invalidStartTime == 0)
				invalidStartTime = GetTickCount64();
			else if (GetTickCount64() - invalidStartTime >= 2000)
			{
				gunCaliberIndex = 0;
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			continue;
		}
		else
		{
			invalidStartTime = 0;
		}

		CCurrentWeaponCaliber* gunCaliber = reinterpret_cast<CCurrentWeaponCaliber*>(caliberPtr);
		gunCaliber->GunCaliber = gunCaliberModes[gunCaliberIndex];

		// Check for NUMPAD9 to cycle
		if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		{
			WaitForKeyRelease(VK_NUMPAD9);
			gunCaliberIndex++;
			if (gunCaliberIndex >= 5)
			{
				gunCaliberIndex = 0;
				gunCaliber->GunCaliber = gunCaliberModes[gunCaliberIndex];
				system("cls");
				showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
				break;
			}
			system("cls");
			showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled, infiniteGadgetEnabled, goOutsideEnabled, gunCaliberIndex);
		}
	}
}
