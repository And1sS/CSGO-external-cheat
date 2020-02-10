#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <cmath>

#include "MemManager.h"
#include "BaseEntity.h"
#include "Vec3.h"
#include "Hacks.h";

#define CLIENT_PANORAMA L"client_panorama.dll"
#define ENGINE L"Engine.dll"
#define WINDOW_NAME L"Counter-Strike: Global Offensive"

//#define DEBUG

uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName);

int main()
{
    HANDLE processHandle = 0;
    unsigned char _junk[33];
    DWORD pid = 0;
    unsigned char _junk2[71];
    HWND hWND = FindWindow(NULL, WINDOW_NAME);

    while (hWND == NULL)
    {
        system("cls");
        std::cout << "Counter-Strike: Global Offensive is not running" << std::endl;
        hWND = FindWindow(NULL, WINDOW_NAME);
        Sleep(100);
    }
    
    GetWindowThreadProcessId(hWND, &pid);
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
    while (processHandle == NULL)
    {
        system("cls");
        std::cout << "Counter-Strike: Global Offensive successfully found." << std::endl;
        std::cout << "Open process failed, retrying.." << std::endl;
        GetWindowThreadProcessId(hWND, &pid);
        processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
        Sleep(100);
    }

    system("cls");
    std::cout << "Counter-Strike: Global Offensive successfully found." << std::endl;
    std::cout << "Counter-Strike: Global Offensive process successfully opened." << std::endl;

    uintptr_t clientPanoramaDllAddress = getModuleBaseAddress(pid, CLIENT_PANORAMA);
    while (clientPanoramaDllAddress == NULL)
    {
        std::cout << "finding module base address failed, retrying.." << std::endl;
        clientPanoramaDllAddress = getModuleBaseAddress(pid, CLIENT_PANORAMA);
    }

    system("cls");
    std::cout << "Counter-Strike: Global Offensive successfully found." << std::endl;
    std::cout << "Counter-Strike: Global Offensive process successfully opened." << std::endl;
    std::cout << "Module base successfully found." << std::endl;

    MemManager* memManager = new MemManager(processHandle, clientPanoramaDllAddress);
    Hacks hacks(memManager);

    while (true)
    {   
        hacks.loadEntityList();

#ifdef DEBUG
        hacks.printEntitiesInfo();
#endif

        hacks.triggerBot();
        hacks.glowESP();
        hacks.antiFlash();
        hacks.bunnyHop();

    }
    std::cin.get();
}

uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    unsigned char _junk[11];
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        unsigned char _junk[6];
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

