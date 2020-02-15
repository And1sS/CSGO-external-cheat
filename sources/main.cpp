#include <QApplication>

#include "MemManager.h"
#include "BaseEntity.h"
#include "Vec3.h"
#include "Hacks.h"
#include "mainwindow.h"

#define CLIENT_PANORAMA L"client_panorama.dll"
#define ENGINE L"Engine.dll"
#define WINDOW_NAME L"Counter-Strike: Global Offensive"

//#define DEBUG

uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    HANDLE processHandle = 0;
    unsigned char _junk[33];
    DWORD pid = 0;
    unsigned char _junk2[71];
    HWND hWND = FindWindow(NULL, WINDOW_NAME);

    window.setStatusColour(Qt::red);
    window.setStatus("Status: Counter-Strike: Global Offensive is not running");
    window.disableAllCheckboxes();

    while (hWND == NULL)
    {
        QCoreApplication::processEvents();
        hWND = FindWindow(NULL, WINDOW_NAME);

#ifdef DEBUG
        system("cls");
        std::cout << "Counter-Strike: Global Offensive is not running" << std::endl;
#endif
    }

    GetWindowThreadProcessId(hWND, &pid);
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
    window.setStatus("Status: Open process failed, retrying..");

    while (processHandle == NULL)
    {
        QCoreApplication::processEvents();
        GetWindowThreadProcessId(hWND, &pid);
        processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);

#ifdef DEBUG
        system("cls");
        std::cout << "Counter-Strike: Global Offensive successfully found."     << std::endl;
        std::cout << "Open process failed, retrying.."                          << std::endl;
#endif
    }

#ifdef DEBUG
    system("cls");
    std::cout << "Counter-Strike: Global Offensive successfully found."          << std::endl;
    std::cout << "Counter-Strike: Global Offensive process successfully opened." << std::endl;
#endif

    DWORD clientPanoramaDllAddress = getModuleBaseAddress(pid, CLIENT_PANORAMA);
    DWORD engineDllAddress = getModuleBaseAddress(pid, ENGINE);

    window.setStatus("Status: Finding module base address failed, retrying..");

    while (clientPanoramaDllAddress == NULL || engineDllAddress == NULL)
    {
        QCoreApplication::processEvents();
        clientPanoramaDllAddress = getModuleBaseAddress(pid, CLIENT_PANORAMA);
        engineDllAddress = getModuleBaseAddress(pid, ENGINE);

#ifdef DEBUG
        system("cls");
        std::cout << "finding module base address failed, retrying.." << std::endl;
#endif
    }

#ifdef DEBUG
    system("cls");
    std::cout << "Counter-Strike: Global Offensive successfully found."          << std::endl;
    std::cout << "Counter-Strike: Global Offensive process successfully opened." << std::endl;
    std::cout << "Module base successfully found."                               << std::endl;
#endif

    MemManager* memManager = new MemManager(processHandle, clientPanoramaDllAddress, engineDllAddress);
    Hacks hacks(memManager);

    window.setStatus("Status: Game process and modules are found.");
    window.setStatusColour(Qt::green);
    window.enableAllCheckboxes();
    window.setHacks(&hacks);

    while (true)
    {
        QCoreApplication::processEvents();
        if (window.isHidden())
        {
            break;
        }

        hacks.loadEntityList();
        hacks.antiFlash();
        hacks.glowESP();
        hacks.triggerBot();
        hacks.bunnyHop();

#ifdef DEBUG
        system("cls");
        hacks.printEntitiesInfo();
#endif
    }

    CloseHandle(processHandle);
    return a.exec();
}

int junkFunc(const int& h)
{
    DWORD64 tmp = 0x0941449 & h;
    return tmp;
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
                unsigned char _junk[23];
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    junkFunc(5);
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

