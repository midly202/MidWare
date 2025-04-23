#define WIN_32_LEAN_AND_MEAN
#include "functions.h"

// global flags
uintptr_t baseAddress = (uintptr_t)GetModuleHandleA("RainbowSix.exe");
HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
CCurrentWeapon2* currentWeapon2 = NULL;
CCurrentWeapon3* currentWeapon3 = NULL;
CCurrentWeapon4* currentWeapon4 = NULL;
CCurrentWeapon5* currentWeapon5 = NULL;
CPlayer* player = NULL;
Settings* settings = NULL;
WeaponComponent* weaponComponent = NULL;
ESP* esp = NULL;

// CHANGE THIS ACCORDINGLY!
const char* GlowEsp = "D:\\GlowESP\\ExtBytePatch.exe";

bool noRecoilEnabled = false;
bool fireRateEnabled = false;
bool infiniteAmmoEnabled = false;
bool powerfulAmmoEnabled = false;
bool noSpreadEnabled = false;
bool movementSpeedEnabled = false;
bool fishEyeEnabled = false;
bool glowEspEnabled = false;

bool thread1Running = true;
bool thread2Running = true;
bool thread3Running = true;
bool thread4Running = true;
bool thread5Running = true;
bool thread6Running = true;
bool thread7Running = true;
bool thread8Running = true;

void Initialization(HMODULE instance) noexcept
{
    AllocConsole();
    FILE* f = nullptr;
    freopen_s(&f, "CONOUT$", "w", stdout);
    system("cls");
    showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled);

    // wait for uninjection process
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
    }
    
    // cleanup
    Sleep(100);
    while (!CanUninject(thread1Running, thread2Running, thread3Running, thread4Running, thread5Running, thread6Running, thread7Running, thread8Running))
    {
        std::cout << "Cannot uninject yet! Threads still running.\n";
        Sleep(100);
    }
    if (f) fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
}

void OverwriteOpcodes(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
        {
            WaitForKeyRelease(VK_NUMPAD8);

            uintptr_t espPtr = GetPointer(baseAddress, offsets::ESP);
            if (!espPtr)
                continue;
            ESP* esp = reinterpret_cast<ESP*>(espPtr);
            if (esp->espOutlineThickness != 2.5)
                esp->espOutlineThickness = 2.5;

            glowEspEnabled = !glowEspEnabled;
            CallExternal(GlowEsp);

            if (glowEspEnabled)
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled);
            }
            else
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled);
            }
        }
        Sleep(10);
    }

    thread1Running = false;
}

void NoRecoil(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
        {
            ToggleNoRecoil();
            if (noRecoilEnabled)
                MaintainNoRecoil();
        }
    }

    thread2Running = false;
}

void FireRate(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
        {
            ToggleFireRate();
            if (fireRateEnabled)
                MaintainFireRate();
        }
    }

    thread3Running = false;
}

void InfiniteAmmo(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
        {
            ToggleInfiniteAmmo();
            if (infiniteAmmoEnabled)
                MaintainInfiniteAmmo();
        }
    }

    thread4Running = false;
}

void PowerfulAmmo(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
        {
            TogglePowerfulAmmo();
            if (powerfulAmmoEnabled)
                MaintainPowerfulAmmo();
        }
    }

    thread5Running = false;
}

void NoSpread(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
        {
            ToggleNoSpread();
            if (noSpreadEnabled)
                MaintainNoSpread();
        }
    }

    thread6Running = false;
}

void MovementSpeed(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
        {
            ToggleMovementSpeed();
            if (movementSpeedEnabled)
                MaintainMovementSpeed();
        }
    }

    thread7Running = false;
}

void FishEye(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
        {
            ToggleFishEye();
            if (fishEyeEnabled)
                MaintainFishEye();
        }
    }

    thread8Running = false;
}

int __stdcall DllMain(HMODULE instance, std::uintptr_t reason, const void* reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);
        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialization), instance, 0, nullptr);
        if (thread) CloseHandle(thread);
        const auto thread2 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(OverwriteOpcodes), instance, 0, nullptr);
        if (thread2) CloseHandle(thread2);
        const auto thread3 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(NoRecoil), instance, 0, nullptr);
        if (thread3) CloseHandle(thread3);
        const auto thread4 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FireRate), instance, 0, nullptr);
        if (thread4) CloseHandle(thread4);
        const auto thread5 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InfiniteAmmo), instance, 0, nullptr);
        if (thread5) CloseHandle(thread5);
        const auto thread6 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(PowerfulAmmo), instance, 0, nullptr);
        if (thread6) CloseHandle(thread6);
        const auto thread7 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(NoSpread), instance, 0, nullptr);
        if (thread7) CloseHandle(thread7);
        const auto thread8 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MovementSpeed), instance, 0, nullptr);
        if (thread8) CloseHandle(thread8);
        const auto thread9 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FishEye), instance, 0, nullptr);
        if (thread9) CloseHandle(thread9);
        break;
    }

    return TRUE;
}