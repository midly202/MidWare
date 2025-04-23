#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <commdlg.h>
#include <string>
#include <Psapi.h>

// ------------------------------------------------------------------------- \\
// --------------------------------Injection-------------------------------- \\
// ------------------------------------------------------------------------- \\ 

uintptr_t GetProcId(const std::string& procName)
{
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(PROCESSENTRY32);
    uintptr_t pid = 0;  // Using uintptr_t for portability

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "[!] Failed to create process snapshot.\n";
        return 0;
    }

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (_stricmp(entry.szExeFile, procName.c_str()) == 0)
            {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }
    CloseHandle(snapshot);
    return pid;
}

bool InjectDLL(uintptr_t pid, const std::string& dllPath)
{
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc || hProc == INVALID_HANDLE_VALUE)
    {
        std::cerr << "[!] Failed to open target process.\n";
        return false;
    }

    void* allocAddr = VirtualAllocEx(hProc, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!allocAddr)
    {
        std::cerr << "[!] Failed to allocate memory in target process.\n";
        CloseHandle(hProc);
        return false;
    }

    if (!WriteProcessMemory(hProc, allocAddr, dllPath.c_str(), dllPath.length() + 1, nullptr))
    {
        std::cerr << "[!] Failed to write DLL path to target process memory.\n";
        VirtualFreeEx(hProc, allocAddr, 0, MEM_RELEASE);
        CloseHandle(hProc);
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0,
        reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA),
        allocAddr, 0, nullptr);

    if (!hThread)
    {
        std::cerr << "[!] Failed to create remote thread.\n";
        VirtualFreeEx(hProc, allocAddr, 0, MEM_RELEASE);
        CloseHandle(hProc);
        return false;
    }

    CloseHandle(hThread);
    CloseHandle(hProc);
    return true;
}

std::string GetDLLPath()
{
    char filename[MAX_PATH] = {};
    OPENFILENAMEA ofn = { sizeof(ofn) };
    ofn.lpstrFilter = "DLL Files\0*.dll\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrTitle = "Select DLL to Inject";

    return GetOpenFileNameA(&ofn) ? std::string(filename) : "";
}

// ------------------------------------------------------------------------- \\
// -------------------------------ExtBytePatch------------------------------ \\
// ------------------------------------------------------------------------- \\ 

DWORD GetProcessIdByName(const std::string& processName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (processName == entry.szExeFile)
            {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

uintptr_t GetBaseAddress(DWORD processId)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (!hProcess)
        return 0;

    HMODULE hMod[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hMod, sizeof(hMod), &cbNeeded))
    {
        uintptr_t baseAddress = (uintptr_t)hMod[0];
        CloseHandle(hProcess);
        return baseAddress;
    }

    CloseHandle(hProcess);
    return 0;
}

bool ReadByte(HANDLE hProcess, uintptr_t address, uint8_t& outByte)
{
    SIZE_T bytesRead;
    return ReadProcessMemory(hProcess, (LPCVOID)address, &outByte, sizeof(outByte), &bytesRead) && bytesRead == sizeof(outByte);
}

void WriteByte(HANDLE hProcess, uintptr_t address, uint8_t value)
{
    DWORD oldProtect;
    VirtualProtectEx(hProcess, (LPVOID)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);
    SIZE_T bytesWritten;
    WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), &bytesWritten);
    VirtualProtectEx(hProcess, (LPVOID)address, sizeof(value), oldProtect, &oldProtect);
}

// ------------------------------------------------------------------------- \\
// ------------------------------Cheat Functions---------------------------- \\
// ------------------------------------------------------------------------- \\ 

int GlowESP()
{
    DWORD processId = GetProcessIdByName("RainbowSix.exe");
    if (processId == 0) return 1;

    uintptr_t baseAddress = GetBaseAddress(processId);
    if (baseAddress == 0) return 1;

    uintptr_t addressToPatch1 = baseAddress + 0x375b773;
    uintptr_t addressToPatch2 = baseAddress + 0x375be7c;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!hProcess) return 1;

    uint8_t currentByte;
    if (!ReadByte(hProcess, addressToPatch1, currentByte))
    {
        CloseHandle(hProcess);
        return 1;
    }

    // Toggle logic
    uint8_t newValue = (currentByte == 0x74) ? 0x75 : 0x74;
    WriteByte(hProcess, addressToPatch1, newValue);
    WriteByte(hProcess, addressToPatch2, newValue);

    CloseHandle(hProcess);
    return 0;
}