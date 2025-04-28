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
Knife* knife = NULL;
Health* health = NULL;
CNoClip* noClip = NULL;
CCamera* camera = NULL;
CThuntWave* thuntWave = NULL;

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
bool infiniteGadgetEnabled = false;
bool goOutsideEnabled = false;
bool skyBoxEnabled = false;
bool knifeDistanceEnabled = false;
bool godModeEnabled = false;
bool noClipEnabled = false;
bool thirdPersonEnabled = false;
bool droneJumpEnabled = false;
bool droneSpeedEnabled = false;
bool droneGravityEnabled = false;
bool twitchBuffEnabled = false;
bool echoBuffEnabled = false;
bool plantAnywhereEnabled = false;
bool lockWaveEnabled = false;
int gunCaliberIndex = 0;

bool thread1Running = true;
bool thread2Running = true;
bool thread3Running = true;
bool thread4Running = true;
bool thread5Running = true;
bool thread6Running = true;
bool thread7Running = true;
bool thread8Running = true;
bool thread9Running = true;
bool thread10Running = true;
bool thread11Running = true;
bool thread12Running = true;
bool thread13Running = true;
bool thread14Running = true;
bool thread15Running = true;

void Initialization(HMODULE instance) noexcept
{
    AllocConsole();
    FILE* f = nullptr;
    freopen_s(&f, "CONOUT$", "w", stdout);
    system("cls");
    system("mode con: cols=70 lines=42");
    showMenuInit();

    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MySharedMemory");
    if (!hMapFile) return;

    internalFlags* pFlags = (internalFlags*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(internalFlags));
    if (!pFlags) return;

    address1 = FindPattern("RainbowSix.exe", "\x80\xB9\x00\x00\x00\x00\x00\x74\x15\xE8", "xx?????xxx");
    address2 = FindPattern("RainbowSix.exe", "\x80\xB9\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x48\x89\xF1\x31", "xx?????xx????xxxx");

    pFlags->runShootAddy1 = address1;
    pFlags->runShootAddy2 = address2;
    system("cls");
    showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);

    // wait for uninjection process
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F5) & 0x8000)
        {
            WaitForKeyRelease(VK_F5);

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
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
        {
            WaitForKeyRelease(VK_NUMPAD6);

            runShootEnabled = !runShootEnabled;

            if (runShootEnabled)
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
                pFlags->runShoot = true;
            }
            else
            {
                pFlags->runShoot = true;
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
        {
            WaitForKeyRelease(VK_NUMPAD8);

            boltScriptEnabled = !boltScriptEnabled;

            pFlags->boltScript = true;

            if (boltScriptEnabled)
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_F4) & 0x8000)
        {
            WaitForKeyRelease(VK_F4);

            infiniteGadgetEnabled = !infiniteGadgetEnabled;

            pFlags->infGadget = true;

            if (infiniteGadgetEnabled)
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_NEXT) & 0x8000)
        {
            WaitForKeyRelease(VK_NEXT);

            goOutsideEnabled = !goOutsideEnabled;

            pFlags->goOutside = true;

            if (goOutsideEnabled)
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_F7) & 0x8000)
        {
            WaitForKeyRelease(VK_F7);

            uintptr_t lightMgrPtr = GetPointer(baseAddress, offsets::LightManager);
            if (!lightMgrPtr)
                continue;
            Skybox* skybox = reinterpret_cast<Skybox*>(lightMgrPtr);

            skyBoxEnabled = !skyBoxEnabled;

            if (skyBoxEnabled)
            {
                skybox->SkyBox = 0;
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                skybox->SkyBox = 1;
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
        }

        else if (GetAsyncKeyState(VK_F8) & 0x8000)
        {
            WaitForKeyRelease(VK_F8);

            uintptr_t settingsPtr = GetPointer(baseAddress, offsets::Settings);
            uintptr_t cameraPtr = GetPointer(baseAddress, offsets::Camera);
            if (!cameraPtr || !settingsPtr)
                continue;
            CCamera* camera = reinterpret_cast<CCamera*>(cameraPtr);
            Settings* settings = reinterpret_cast<Settings*>(settingsPtr);

            thirdPersonEnabled = !thirdPersonEnabled;

            if (thirdPersonEnabled)
            {
                camera->CameraY = -1.2;
                settings->GunFOV = 2.6;
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            else
            {
                camera->CameraY = 0;
                settings->GunFOV = 0.873;
                system("cls");
                showMenu(infiniteAmmoEnabled, fireRateEnabled, noRecoilEnabled, noSpreadEnabled, powerfulAmmoEnabled, runShootEnabled, gunCaliberIndex, boltScriptEnabled, knifeDistanceEnabled, godModeEnabled, movementSpeedEnabled, noClipEnabled, infiniteGadgetEnabled, glowEspEnabled, fishEyeEnabled, skyBoxEnabled, thirdPersonEnabled, droneSpeedEnabled, droneGravityEnabled, twitchBuffEnabled, lockWaveEnabled, goOutsideEnabled);
            }
            }

        Sleep(10);
    }

    // cleanup
    Sleep(100);
    pFlags->exit = true;
    while (!CanUninject(thread1Running, thread2Running, thread3Running, thread4Running, thread5Running, thread6Running, thread7Running, thread8Running, thread9Running, thread10Running, thread11Running, thread12Running, thread13Running, thread14Running))
    {
        std::cout << "Cannot uninject yet! Threads still running.\n";
        Sleep(100);
    }
    if (f) fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
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

    thread1Running = false;
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

    thread2Running = false;
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

    thread3Running = false;
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

    thread4Running = false;
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

    thread5Running = false;
}

void MovementSpeed(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F2) & 0x8000)
        {
            ToggleMovementSpeed();
            if (movementSpeedEnabled)
                MaintainMovementSpeed();
        }
    }

    thread6Running = false;
}

void FishEye(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F6) & 0x8000)
        {
            ToggleFishEye();
            if (fishEyeEnabled)
                MaintainFishEye();
        }
    }

    thread7Running = false;
}

void GunCaliber(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
        {
            HandleGunCaliber();
        }
    }

    thread8Running = false;
}

void KnifeDistance(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
        {
            ToggleKnifeDistance();
            if (knifeDistanceEnabled)
                MaintainKnifeDistance();
        }
    }

    thread9Running = false;
}

void GodMode(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F1) & 0x8000)
        {
            ToggleGodMode();
            if (godModeEnabled)
                MaintainGodMode();
        }
    }

    thread10Running = false;
}

void NoClip(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F3) & 0x8000)
        {
            ToggleNoClip();
            if (noClipEnabled)
                MaintainNoClip();
        }
    }

    thread11Running = false;
}

void DroneSpeed(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F10) & 0x8000)
        {
            ToggleDroneSpeed();
            if (droneSpeedEnabled)
                MaintainDroneSpeed();
        }
    }

    thread12Running = false;
}

void DroneGravity(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F9) & 0x8000)
        {
            ToggleDroneGravity();
            if (droneGravityEnabled)
                MaintainDroneGravity();
        }
    }

    thread13Running = false;
}

void TwitchBuff(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_F11) & 0x8000)
        {
            ToggleTwitchBuff();
            if (twitchBuffEnabled)
                MaintainTwitchBuff();
        }
    }

    thread14Running = false;
}

void LockWave(HMODULE instance) noexcept
{
    while (!GetAsyncKeyState(VK_NUMPAD0))
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_PRIOR) & 0x8000)
        {
            ToggleLockWave();
            if (lockWaveEnabled)
                MaintainLockWave();
        }
    }

    thread15Running = false;
}

int __stdcall DllMain(HMODULE instance, std::uintptr_t reason, const void* reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);
        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialization), instance, 0, nullptr);
        if (thread) CloseHandle(thread);
        const auto thread2 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(NoRecoil), instance, 0, nullptr);
        if (thread2) CloseHandle(thread2);
        const auto thread3 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FireRate), instance, 0, nullptr);
        if (thread3) CloseHandle(thread3);
        const auto thread4 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InfiniteAmmo), instance, 0, nullptr);
        if (thread4) CloseHandle(thread4);
        const auto thread5 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(PowerfulAmmo), instance, 0, nullptr);
        if (thread5) CloseHandle(thread5);
        const auto thread6 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(NoSpread), instance, 0, nullptr);
        if (thread6) CloseHandle(thread6);
        const auto thread7 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MovementSpeed), instance, 0, nullptr);
        if (thread7) CloseHandle(thread7);
        const auto thread8 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FishEye), instance, 0, nullptr);
        if (thread8) CloseHandle(thread8);
        const auto thread9 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GunCaliber), instance, 0, nullptr);
        if (thread9) CloseHandle(thread9);
        const auto thread10 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(KnifeDistance), instance, 0, nullptr);
        if (thread10) CloseHandle(thread10);
        const auto thread11 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GodMode), instance, 0, nullptr);
        if (thread11) CloseHandle(thread11);
        const auto thread12 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(NoClip), instance, 0, nullptr);
        if (thread12) CloseHandle(thread12);
        const auto thread13 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DroneSpeed), instance, 0, nullptr);
        if (thread13) CloseHandle(thread13);
        const auto thread14 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DroneGravity), instance, 0, nullptr);
        if (thread14) CloseHandle(thread14);
        const auto thread15 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(TwitchBuff), instance, 0, nullptr);
        if (thread15) CloseHandle(thread15);
        const auto thread16 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LockWave), instance, 0, nullptr);
        if (thread16) CloseHandle(thread16);
        break;
    }

    return TRUE;
}