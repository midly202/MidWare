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
extern Health* health;
extern CNoClip* noClip;
extern CThuntWave* thuntWave;

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
extern bool knifeDistanceEnabled;
extern bool godModeEnabled;
extern bool noClipEnabled;
extern bool thirdPersonEnabled;
extern bool droneJumpEnabled;
extern bool droneSpeedEnabled;
extern bool droneGravityEnabled;
extern bool twitchBuffEnabled;
extern bool echoBuffEnabled;
extern bool plantAnywhereEnabled;
extern bool lockWaveEnabled;
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
float originalKnifeValue1 = 1.3;
float originalKnifeValue2 = 1.3;
float originalNoClipValue;

uint32_t gunCaliberModes[] = {
	3864566559, // Regular Rifle
	//224916230 // Regular Pistol
	//1635385480// Regular SMG
	1216095593, // Skeleton Key
	3683118896, // Kali's Sniper
	2249646560, // Tachanka's DP27
	//54247478  // Tachanka's DP27 (stationary turret) 
	2097060903  // Maverick's Blowtorch
	//1800674797// Maestro's Turret
	//1586594484// BOSG
	//1314319139// Bailiff
};

// ------------------------------------------------------------------------- \\
// -----------------------------Helper Functions---------------------------- \\
// ------------------------------------------------------------------------- \\ 

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

void WaitForKeyRelease(int vkKey)
{
	while (GetAsyncKeyState(vkKey)) Sleep(10);
}

bool CanUninject(bool thread1Running, bool thread2Running, bool thread3Running, bool thread4Running, bool thread5Running, bool thread6Running, bool thread7Running, bool thread8Running, bool thread9Running, bool thread10Running, bool thread11Running, bool thread12Running, bool thread13Running, bool thread14Running)
{
	if (thread1Running || thread2Running || thread3Running || thread4Running || thread5Running || thread6Running || thread7Running || thread8Running || thread9Running || thread10Running || thread11Running || thread12Running || thread13Running || thread14Running)
		return false; // Returns false if a thread is still running
	else
		return true; // Returns true if all threads have exited
}

uintptr_t GetPointer(uintptr_t base, const std::vector<uintptr_t>& offsets)
{
	uintptr_t addr = base;
	MEMORY_BASIC_INFORMATION mbi;

	for (auto offset : offsets)
	{
		uintptr_t ptrToCheck = addr + offset;

		if (!VirtualQuery((void*)ptrToCheck, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT)
			return 0; // invalid memory, abort

		addr = *(uintptr_t*)ptrToCheck;
	}
	return addr;
}


// ------------------------------------------------------------------------- \\
// ------------------------------Cheat Functions---------------------------- \\
// ------------------------------------------------------------------------- \\ 

void showMenuInit()
{
	std::cout << RED + BOLD << R"(
 +-----------------------------------------+
 |     /\___/\                             |
 |    ( o   o )   Injected!                |
 |    (  =^=  )                            |
 |    (        )                           |
 |    (         ) )" << INVERT + "Scanning for patterns..." + RESET + RED + BOLD << R"( |
 |    (          )))))))))))))))           |
 +-----------------------------------------+
)" << RESET;

	std::cout << RED + BOLD + INVERT +
		" WARNING: FEATURES WRITTEN IN RED ARE UNSTABLE AND CAN CAUSE CRASHES. \n" + RESET;

	std::cout << BOLD + RGB_PURPLE + " Weapon" + RESET << "\n";
	std::cout << " [NUM1] [" << RED + "OFF" + RESET << "] Infinite Ammo\n";
	std::cout << " [NUM2] [" << RED + "OFF" + RESET << "] Rapid Fire\n";
	std::cout << " [NUM3] [" << RED + "OFF" + RESET << "] No Recoil\n";
	std::cout << " [NUM4] [" << RED + "OFF" + RESET << "] No Spread\n";
	std::cout << " [NUM5] [" << RED + "OFF" + RESET << "] Instant Kill\n";
	std::cout << " [NUM6] [" << RED + "OFF" + RESET << "] Run and Shoot\n";
	std::cout << " [NUM7] [" << RED + "OFF" + RESET + "] Gun Caliber " << "\n";
	std::cout << " [NUM8] [" << RED + "OFF" + RESET << "] Remove Pump Action / Bolt Action\n";
	std::cout << " [NUM9] [" << RED + "OFF" + RESET << "]" + RED + " Knife Reach" + RESET + "\n\n";

	std::cout << BOLD + RGB_PURPLE + " Player" + RESET << "\n";
	std::cout << " [F1]   [" << RED + "OFF" + RESET << "] GodMode\n";
	std::cout << " [F2]   [" << RED + "OFF" + RESET + "] Player Speed\n";
	std::cout << " [F3]   [" << RED + "OFF" + RESET << "] NoClip\n";
	std::cout << " [F4]   [" << RED + "OFF" + RESET << "] Infinite Gadgets\n\n";

	std::cout << BOLD + RGB_PURPLE + " Visual" + RESET << "\n";
	std::cout << " [F5]   [" << RED + "OFF" + RESET << "] Glow ESP\n";
	std::cout << " [F6]   [" << RED + "OFF" + RESET << "] Fisheye FOV\n";
	std::cout << " [F7]   [" << RED + "OFF" + RESET << "] Remove Sky\n";
	std::cout << " [F8]   [" << RED + "OFF" + RESET << "]" + RED + " Third Person\n\n";

	std::cout << BOLD + RGB_PURPLE + " Drone" + RESET << "\n";
	std::cout << " [F9]   [" << RED + "OFF" + RESET << "] No Gravity\n";
	std::cout << " [F10]  [" << RED + "OFF" + RESET << "] Drone Speed\n";
	std::cout << " [F11]  [" << RED + "OFF" + RESET << "] Twitch / Echo Buff\n\n";

	std::cout << BOLD + RGB_PURPLE + " Protect Hostage" + RESET << "\n";
	std::cout << " [PGUP] [" << RED + "OFF" + RESET << "] Lock Wave\n";
	std::cout << " [PGDN] [" << RED + "OFF" + RESET << "] Can Go Outside\n";
}

void showMenu(bool infiniteAmmo, bool fireRate, bool noRecoil, bool noSpread, bool powerfulAmmo, bool runShoot, int caliber, bool boltScript, bool knifeDistance, bool godMode, bool movementSpeed, bool noClip, bool infGadget, bool glowEsp, bool fishEye, bool skybox, bool thirdPerson, bool droneSpeed, bool droneGravity, bool twitchBuff, bool lockWave, bool goOutside)
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
 |    (         ) )" << BLINK + RED + "[NUM0] Uninject" + RESET + RGB_PURPLE + BOLD << R"(          |
 |    (          )))))))))))))))           |
 +-----------------------------------------+
)" << RESET << "\n";

	std::cout << BOLD + RGB_PURPLE + " Weapon" + RESET << "\n";
	std::cout << " [NUM1] [" << (infiniteAmmo ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Infinite Ammo\n";
	std::cout << " [NUM2] [" << (fireRate ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Rapid Fire\n";
	std::cout << " [NUM3] [" << (noRecoil ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] No Recoil\n";
	std::cout << " [NUM4] [" << (noSpread ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] No Spread\n";
	std::cout << " [NUM5] [" << (powerfulAmmo ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Instant Kill\n";
	std::cout << " [NUM6] [" << (runShoot ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Run and Shoot\n";
	std::cout << " [NUM7] " << caliberToggle << " Gun Caliber " << caliberText << "\n";
	std::cout << " [NUM8] [" << (boltScript ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Remove Pump Action / Bolt Action\n";
	std::cout << " [NUM9] [" << (knifeDistance ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Knife Reach\n\n";

	std::cout << BOLD + RGB_PURPLE + " Player" + RESET << "\n";
	std::cout << " [F1]   [" << (godMode ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] GodMode\n";
	std::cout << " [F2]   [" << (movementSpeed ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Player Speed\n";
	std::cout << " [F3]   [" << (noClip ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] NoClip\n";
	std::cout << " [F4]   [" << (infGadget ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Infinite Gadgets\n\n";

	std::cout << BOLD + RGB_PURPLE + " Visual" + RESET << "\n";
	std::cout << " [F5]   [" << (glowEsp ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Glow ESP\n";
	std::cout << " [F6]   [" << (fishEye ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Fisheye FOV\n";
	std::cout << " [F7]   [" << (skybox ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Remove Sky\n";
	std::cout << " [F8]   [" << (thirdPerson ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Third Person\n\n";

	std::cout << BOLD + RGB_PURPLE + " Drone" + RESET << "\n";
	std::cout << " [F9]   [" << (droneGravity ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] No Gravity\n";
	std::cout << " [F10]  [" << (droneSpeed ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Drone Speed\n";
	std::cout << " [F11]  [" << (twitchBuff ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Twitch / Echo Buff\n\n";

	std::cout << BOLD + RGB_PURPLE + " Protect Hostage" + RESET << "\n";
	std::cout << " [PGUP] [" << (lockWave ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Lock Wave\n";
	std::cout << " [PGDN] [" << (goOutside ? GREEN + "ON" + RESET : RED + "OFF" + RESET) << "] Can Go Outside\n";
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
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			else if (GetTickCount64() - invalidStartTime >= 2000)
			{
				infiniteAmmoEnabled = false;
				fireRateEnabled = false;
				noRecoilEnabled = false;
				noSpreadEnabled = false;
				powerfulAmmoEnabled = false;
				gunCaliberIndex = 0;
				knifeDistanceEnabled = false;
				godModeEnabled = false;
				movementSpeedEnabled = false;
				droneSpeedEnabled = false;
				droneGravityEnabled = false;
				twitchBuffEnabled = false;
				system("cls");
				showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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

		bool valid = weaponPtr1 && weaponPtr2 && weaponPtr3;

		if (!valid)
			continue;

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
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		WeaponComponent* weaponComponent = reinterpret_cast<WeaponComponent*>(weaponPtr);
		weaponComponent->gunAmmo = 9999;


		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
		{
			infiniteAmmoEnabled = false;
			weaponComponent->gunAmmo = originalAmmoValue;
			WaitForKeyRelease(VK_NUMPAD1);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		CCurrentWeapon4* currentWeapon4 = reinterpret_cast<CCurrentWeapon4*>(weaponPtr);
		currentWeapon4->GunDamage = 9999;


		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			powerfulAmmoEnabled = false;
			currentWeapon4->GunDamage = originalGunDamageValue;
			WaitForKeyRelease(VK_NUMPAD5);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		CCurrentWeapon5* currentWeapon5 = reinterpret_cast<CCurrentWeapon5*>(weaponPtr);
		currentWeapon5->GunSpread = 0;


		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			noSpreadEnabled = false;
			currentWeapon5->GunSpread = originalGunSpreadValue;
			WaitForKeyRelease(VK_NUMPAD4);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	WaitForKeyRelease(VK_F2);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		CPlayer* player = reinterpret_cast<CPlayer*>(playerPtr);
		player->PlayerSpeed = 250;


		if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			movementSpeedEnabled = false;
			player->PlayerSpeed = originalPlayerSpeedValue;
			WaitForKeyRelease(VK_F2);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
	}
	WaitForKeyRelease(VK_F6);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		Settings* settings = reinterpret_cast<Settings*>(settingsPtr);
		settings->PlayerFOV = 2.6;


		if (GetAsyncKeyState(VK_F6) & 0x8000)
		{
			fishEyeEnabled = false;
			settings->PlayerFOV = originalPlayerFovValue;
			WaitForKeyRelease(VK_F6);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
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
			continue;

		CCurrentWeaponCaliber* gunCaliber = reinterpret_cast<CCurrentWeaponCaliber*>(caliberPtr);
		gunCaliber->GunCaliber = gunCaliberModes[gunCaliberIndex];

		// Check for NUMPAD9 to cycle
		if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
		{
			WaitForKeyRelease(VK_NUMPAD7);
			gunCaliberIndex++;
			if (gunCaliberIndex >= 5)
			{
				gunCaliberIndex = 0;
				gunCaliber->GunCaliber = gunCaliberModes[gunCaliberIndex];
				system("cls");
				showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
				break;
			}
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
		}
	}
}

void ToggleKnifeDistance()
{
	knifeDistanceEnabled = !knifeDistanceEnabled;
	if (knifeDistanceEnabled)
	{
		uintptr_t knifePtr = GetPointer(baseAddress, offsets::Knife);
		if (!knifePtr || IsBadReadPtr(reinterpret_cast<void*>(knifePtr), sizeof(Knife)))
		{
			knifeDistanceEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_NUMPAD9);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainKnifeDistance()
{
	ULONGLONG invalidStartTime = 0;

	while (knifeDistanceEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t knifePtr = GetPointer(baseAddress, offsets::Knife);
		bool valid = knifePtr && !IsBadReadPtr(reinterpret_cast<void*>(knifePtr), sizeof(Knife));

		if (!valid)
		{
			knifeDistanceEnabled = false;
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}

		Knife* knife = reinterpret_cast<Knife*>(knifePtr);
		if (knife->knifeDistancePlayers == 1.3f)
			knife->knifeDistancePlayers = 9999.000f;
		if (knife->knifeDistanceWalls == 1.3f)
			knife->knifeDistanceWalls = 9999.000f;


		if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		{
			knifeDistanceEnabled = false;
			knife->knifeDistancePlayers = 1.3f;
			knife->knifeDistanceWalls = 1.3f;
			WaitForKeyRelease(VK_NUMPAD9);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleGodMode()
{
	godModeEnabled = !godModeEnabled;
	if (godModeEnabled)
	{
		uintptr_t healthPtr = GetPointer(baseAddress, offsets::GodMode);
		if (!healthPtr || IsBadReadPtr(reinterpret_cast<void*>(healthPtr), sizeof(Health)))
		{
			godModeEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_F1);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainGodMode()
{
	ULONGLONG invalidStartTime = 0;

	while (godModeEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t healthPtr = GetPointer(baseAddress, offsets::GodMode);
		bool valid = healthPtr && !IsBadReadPtr(reinterpret_cast<void*>(healthPtr), sizeof(Health));

		if (!valid)
			continue;

		Health* health = reinterpret_cast<Health*>(healthPtr);
		health->Health = 9999;


		if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			godModeEnabled = false;
			health->Health = 120;
			WaitForKeyRelease(VK_F1);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleNoClip()
{
	noClipEnabled = !noClipEnabled;
	if (noClipEnabled)
	{
		uintptr_t noClipPtr = GetPointer(baseAddress, offsets::NoClip);
		if (!noClipPtr || IsBadReadPtr(reinterpret_cast<void*>(noClipPtr), sizeof(CNoClip)))
		{
			noClipEnabled = false;
			return;
		}
		CNoClip* noClip = reinterpret_cast<CNoClip*>(noClipPtr);
		originalNoClipValue = noClip->NoClip;
	}
	WaitForKeyRelease(VK_F3);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainNoClip()
{
	ULONGLONG invalidStartTime = 0;

	while (noClipEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t noClipPtr = GetPointer(baseAddress, offsets::NoClip);
		bool valid = noClipPtr && !IsBadReadPtr(reinterpret_cast<void*>(noClipPtr), sizeof(CNoClip));

		if (!valid)
			continue;

		CNoClip* noClip = reinterpret_cast<CNoClip*>(noClipPtr);
		noClip->NoClip = -1;


		if (GetAsyncKeyState(VK_F3) & 0x8000)
		{
			noClipEnabled = false;
			noClip->NoClip = originalNoClipValue;
			WaitForKeyRelease(VK_F3);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleDroneSpeed()
{
	droneSpeedEnabled = !droneSpeedEnabled;
	if (droneSpeedEnabled)
	{
		uintptr_t drone3Ptr = GetPointer(baseAddress, offsets::Drone3);
		if (!drone3Ptr || IsBadReadPtr(reinterpret_cast<void*>(drone3Ptr), sizeof(CDrone3)))
		{
			droneSpeedEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_F10);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainDroneSpeed()
{
	ULONGLONG invalidStartTime = 0;

	while (droneSpeedEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t drone3Ptr = GetPointer(baseAddress, offsets::Drone3);
		bool valid = drone3Ptr && !IsBadReadPtr(reinterpret_cast<void*>(drone3Ptr), sizeof(CDrone3));

		if (!valid)
			continue;

		CDrone3* drone3 = reinterpret_cast<CDrone3*>(drone3Ptr);
		drone3->DroneTopSpeed = 10;
		drone3->DroneAcceleration = 100;


		if (GetAsyncKeyState(VK_F10) & 0x8000)
		{
			droneSpeedEnabled = false;
			drone3->DroneTopSpeed = 3.5;
			drone3->DroneAcceleration = 4;
			WaitForKeyRelease(VK_F10);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleDroneGravity()
{
	droneGravityEnabled = !droneGravityEnabled;
	if (droneGravityEnabled)
	{
		uintptr_t drone2Ptr = GetPointer(baseAddress, offsets::Drone2);
		if (!drone2Ptr || IsBadReadPtr(reinterpret_cast<void*>(drone2Ptr), sizeof(CDrone2)))
		{
			droneGravityEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_F9);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainDroneGravity()
{
	ULONGLONG invalidStartTime = 0;

	while (droneGravityEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t drone2Ptr = GetPointer(baseAddress, offsets::Drone2);
		bool valid = drone2Ptr && !IsBadReadPtr(reinterpret_cast<void*>(drone2Ptr), sizeof(CDrone2));

		if (!valid)
			continue;

		CDrone2* drone2 = reinterpret_cast<CDrone2*>(drone2Ptr);
		drone2->DroneGravity = 0;


		if (GetAsyncKeyState(VK_F9) & 0x8000)
		{
			droneGravityEnabled = false;
			drone2->DroneGravity = -9.800;
			WaitForKeyRelease(VK_F9);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleTwitchBuff()
{
	twitchBuffEnabled = !twitchBuffEnabled;
	if (twitchBuffEnabled)
	{
		uintptr_t drone1Ptr = GetPointer(baseAddress, offsets::Drone1);
		uintptr_t drone2Ptr = GetPointer(baseAddress, offsets::Drone2);
		if (!drone1Ptr || !drone2Ptr  || IsBadReadPtr(reinterpret_cast<void*>(drone1Ptr), sizeof(CDrone1)) || IsBadReadPtr(reinterpret_cast<void*>(drone2Ptr), sizeof(CDrone2)))
		{
			twitchBuffEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_F11);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainTwitchBuff()
{
	ULONGLONG invalidStartTime = 0;

	while (twitchBuffEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t drone1Ptr = GetPointer(baseAddress, offsets::Drone1);
		uintptr_t drone2Ptr = GetPointer(baseAddress, offsets::Drone2);
		bool valid = drone1Ptr && drone2Ptr && !IsBadReadPtr(reinterpret_cast<void*>(drone1Ptr), sizeof(CDrone1)) && !IsBadReadPtr(reinterpret_cast<void*>(drone2Ptr), sizeof(CDrone2));

		if (!valid)
			continue;

		CDrone1* drone1 = reinterpret_cast<CDrone1*>(drone1Ptr);
		CDrone2* drone2 = reinterpret_cast<CDrone2*>(drone2Ptr);
		drone1->DroneJump = 2;
		drone1->DroneJumpDelay = 0;
		drone1->DroneMaxAmmo = 2;
		drone1->DroneWeaponReach = 999;
		drone2->DroneAmmo = 1;


		if (GetAsyncKeyState(VK_F11) & 0x8000)
		{
			twitchBuffEnabled = false;
			drone1->DroneJump = 0;
			drone1->DroneJumpDelay = 2;
			drone1->DroneMaxAmmo = 3;
			drone1->DroneWeaponReach = 7;
			drone2->DroneAmmo = 0;
			WaitForKeyRelease(VK_F11);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}

void ToggleLockWave()
{
	lockWaveEnabled = !lockWaveEnabled;
	if (lockWaveEnabled)
	{
		uintptr_t wavePtr = GetPointer(baseAddress, offsets::THuntWave);
		if (!wavePtr || IsBadReadPtr(reinterpret_cast<void*>(wavePtr), sizeof(CThuntWave)))
		{
			lockWaveEnabled = false;
			return;
		}
	}
	WaitForKeyRelease(VK_PRIOR);
	system("cls");
	showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
}

void MaintainLockWave()
{
	ULONGLONG invalidStartTime = 0;

	while (lockWaveEnabled && !GetAsyncKeyState(VK_NUMPAD0))
	{
		Sleep(10);
		uintptr_t wavePtr = GetPointer(baseAddress, offsets::THuntWave);
		bool valid = wavePtr && !IsBadReadPtr(reinterpret_cast<void*>(wavePtr), sizeof(CThuntWave));

		if (!valid)
			continue;

		CThuntWave* thuntWave = reinterpret_cast<CThuntWave*>(wavePtr);

		thuntWave->CurrentWave = 0;

		if (GetAsyncKeyState(VK_PRIOR) & 0x8000)
		{
			WaitForKeyRelease(VK_PRIOR);
			system("cls");
			showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
			break;
		}
	}
}