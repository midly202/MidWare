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

uintptr_t address1;
uintptr_t address2;

bool noRecoilEnabled = false;
bool fireRateEnabled = false;
bool infiniteAmmoEnabled = false;
bool powerfulAmmoEnabled = false;
bool noSpreadEnabled = false;
bool movementSpeedEnabled = false;
bool fishEyeEnabled = false;
bool glowEspEnabled = false;
bool runShootEnabled = false;
bool boltScriptEnabled = false;
bool skyBoxEnabled = false;

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

    std::cout << BLINK + "[0] Uninject" + RESET << "\n\n";
    std::cout << BOLD + RGB_PURPLE + "Internal" + RESET << "\n";
    std::cout << "[1] [" << RED + "OFF" + RESET << "] Infinite Ammo\n";
    std::cout << "[2] [" << RED + "OFF" + RESET << "] Rapid Fire*\n";
    std::cout << "[3] [" << RED + "OFF" + RESET << "] No Recoil*\n";
    std::cout << "[4] [" << RED + "OFF" + RESET << "] No Spread*\n";
    std::cout << "[5] [" << RED + "OFF" + RESET << "] Instant Kill*\n";
    std::cout << "[6] [" << RED + "OFF" + RESET << "] Speedy Gonzales*\n";
    std::cout << "[7] [" << RED + "OFF" + RESET << "] Fisheye FOV\n";
    std::cout << "[8] [" << RED + "OFF" + RESET << "] Remove Sky\n\n";
    std::cout << BOLD + RGB_PURPLE + "External" + RESET << "\n";
    std::cout << "[F1] [" << RED + "OFF" + RESET << "] Glow ESP\n";
    std::cout << "[F2] [" << RED + "OFF" + RESET << "] Run and Shoot\n";
    std::cout << "[F3] [" << RED + "OFF" + RESET << "] Kali Bolt Script\n";
    std::cout << "\n" + BOLD + BRIGHT_RED +
        "Warning: The game may crash if features marked with a * are left enabled while leaving or joining sessions.\n"
        "         To prevent this, it's recommended to disable those features before transitioning between games." +
        RESET + "\n";

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

void Toggles(HMODULE instance) noexcept
{
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MySharedMemory");
    if (!hMapFile) return;

    internalFlags* pFlags = (internalFlags*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(internalFlags));
    if (!pFlags) return;

    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        if (GetAsyncKeyState(VK_F1) & 0x8000)
        {
            WaitForKeyRelease(VK_F1);

            glowEspEnabled = !glowEspEnabled;

            uintptr_t espPtr = GetPointer(baseAddress, offsets::ESP);
            if (!espPtr)
                continue;
            ESP* esp = reinterpret_cast<ESP*>(espPtr);
            if (esp->espOutlineThickness != 2.5)
                esp->espOutlineThickness = 2.5;

            pFlags->glowESP = true;

            if (glowEspEnabled)
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
            else
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_F2) & 0x8000)
        {
            WaitForKeyRelease(VK_F2);

            runShootEnabled = !runShootEnabled;

            if (runShootEnabled)
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
                if (!address1)
                    address1 = FindPattern("RainbowSix.exe", "\x80\xB9\x00\x00\x00\x00\x00\x74\x15\xE8", "xx?????xxx");
                if (!address2)
                    address2 = FindPattern("RainbowSix.exe", "\x80\xB9\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x48\x89\xF1\x31", "xx?????xx????xxxx");
                pFlags->runShootAddy1 = address1;
                pFlags->runShootAddy2 = address2;
                pFlags->runShoot = true;
            }
            else
            {
                pFlags->runShoot = true;
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_F3) & 0x8000)
        {
            WaitForKeyRelease(VK_F3);

            boltScriptEnabled = !boltScriptEnabled;

            pFlags->boltScript = true;

            if (boltScriptEnabled)
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
            else
            {
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
        {
            WaitForKeyRelease(VK_NUMPAD8);

            uintptr_t lightMgrPtr = GetPointer(baseAddress, offsets::LightManager);
            if (!lightMgrPtr)
                continue;
            Skybox* skybox = reinterpret_cast<Skybox*>(lightMgrPtr);

            skyBoxEnabled = !skyBoxEnabled;

            if (skyBoxEnabled)
            {
				skybox->SkyBox = 0;
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
            else
            {
				skybox->SkyBox = 1;
                system("cls");
                showMenu(noRecoilEnabled, fireRateEnabled, infiniteAmmoEnabled, powerfulAmmoEnabled, noSpreadEnabled, movementSpeedEnabled, fishEyeEnabled, glowEspEnabled, runShootEnabled, boltScriptEnabled, skyBoxEnabled);
            }
        }
        Sleep(10);
    }

    pFlags->exit = true;
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
        const auto thread2 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Toggles), instance, 0, nullptr);
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