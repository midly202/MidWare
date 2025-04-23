#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <commdlg.h>
#include <string>

// Injection
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