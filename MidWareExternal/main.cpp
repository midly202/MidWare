#include "functions.h"

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // ------------------------------------------------------------------------- \\
    // --------------------------------Injection-------------------------------- \\
    // ------------------------------------------------------------------------- \\ 

    std::string dllPath = GetDLLPath();
    if (dllPath.empty())
    {
        return 1;
    }
    std::string procName = "RainbowSix.exe";
    uintptr_t procId = GetProcId(procName);

    if (!InjectDLL(procId, dllPath))
    {
        std::cerr << "[!] Injection failed.\n";
        return 1;
    }

    // ------------------------------------------------------------------------- \\
    // -----------------------------Allocate memory----------------------------- \\
    // ------------------------------------------------------------------------- \\ 

    struct internalFlags
    {
        bool glowESP;
        bool runShoot;
        bool boltScript;
        bool infGadget;
        bool goOutside;
        bool exit;
        uintptr_t runShootAddy1;
        uintptr_t runShootAddy2;
    };

    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
        sizeof(internalFlags), "MySharedMemory");

    if (!hMapFile)
    {
        std::cerr << "Could not create file mapping object. Error: " << GetLastError() << "\n";
        return 1;
    }

    internalFlags* pFlags = (internalFlags*)MapViewOfFile(
        hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(internalFlags));

    if (!pFlags)
    {
        std::cerr << "Could not map view of file. Error: " << GetLastError() << "\n";
        CloseHandle(hMapFile);
        return 1;
    }

    // ------------------------------------------------------------------------- \\
    // --------------------------------Set flags-------------------------------- \\
    // ------------------------------------------------------------------------- \\ 

    pFlags->glowESP = false;
    pFlags->runShoot = false;
    pFlags->boltScript = false;
    pFlags->infGadget = false;
    pFlags->goOutside = false;
    pFlags->exit = false;

    // ------------------------------------------------------------------------- \\
    // --------------------------------Read flags------------------------------- \\
    // ------------------------------------------------------------------------- \\ 

    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, procId);

    while (!pFlags->exit)
    {
        DWORD exitCode = 0;
        if (!GetExitCodeProcess(hProc, &exitCode) || exitCode != STILL_ACTIVE)
            break;

        if (pFlags->glowESP)
        {
            GlowESP();
            pFlags->glowESP = false;
        }
        else if (pFlags->runShoot)
        {
            RunShoot(pFlags->runShootAddy1, pFlags->runShootAddy2);
            pFlags->runShoot = false;
        }
        else if (pFlags->boltScript)
        {
            BoltScript();
            pFlags->boltScript = false;
        }
		else if (pFlags->infGadget)
		{
			InfiniteSecondaryGadgets();
			pFlags->infGadget = false;
		}
		else if (pFlags->goOutside)
		{
			GoOutside();
			pFlags->goOutside = false;
		}

        Sleep(10);
    }

    // ------------------------------------------------------------------------- \\
    // --------------------------Free allocated memory-------------------------- \\
    // ------------------------------------------------------------------------- \\ 

    UnmapViewOfFile(pFlags);
    CloseHandle(hMapFile);
    return 0;
}
