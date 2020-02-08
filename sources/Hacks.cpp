#include "Hacks.h"

Hacks::Hacks(MemManager* memManager)
{
    this->memManager = memManager;

    glowObject = memManager->readMem<DWORD>(
        (LPCVOID)(memManager->getClientPanoramaDllAddress() + memdump::signatures::dwGlowObjectManager));
}

void Hacks::loadEntityList()
{
    entityList.clear();
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        DWORD entityObjectPointer = memManager->getClientPanoramaDllAddress()
            + memdump::signatures::dwEntityList + i * struct_size::player_EntSize;
        BaseEntity entity(memManager, memManager->readMem<DWORD>((LPCVOID)entityObjectPointer));

        if (entity.isValid() != NULL)
        {
            entityList.push_back(entity);
        }
    }
}

void Hacks::printEntitiesInfo()
{
    DWORD localPlayerAddr = memManager->readMem<DWORD>(LPCVOID(memManager->getClientPanoramaDllAddress() + memdump::signatures::dwLocalPlayer));
    BaseEntity localPlayer(memManager, localPlayerAddr);

    system("cls");
    std::cout << "debug mode" << std::endl;
    std::cout << "lp : " << std::hex << localPlayerAddr << std::endl;
    for (int i = 0; i < entityList.size(); i++)
    {
        std::cout << "entity #" << i 
            << "    health address: " << std::hex << entityList[i].getBase() + memdump::netvars::m_iHealth
            << " health: " << std::dec << entityList[i].getHealth()
            << " x: " << entityList[i].getOrigin().getX()
            << " y: " << entityList[i].getOrigin().getY()
            << " z: " << entityList[i].getOrigin().getZ()
            << " team: : " << (entityList[i].getTeam() == 2 ? "T" : "CT")
            << std::endl << std::endl << std::endl;
    }
}

void Hacks::glowESP()
{
    DWORD localPlayerAddr = memManager->readMem<DWORD>(LPCVOID(memManager->getClientPanoramaDllAddress() + memdump::signatures::dwLocalPlayer));
    BaseEntity localPlayer(memManager, localPlayerAddr);

    for (int i = 0; i < entityList.size(); i++)
    {
        if (entityList[i].isValid() != NULL && entityList[i].getBase() != localPlayer.getBase())
        {
            colours entityGlowColour;
            if (entityList[i].getTeam() == localPlayer.getTeam())
                entityGlowColour = { 0, 1, 0, 1 };
            else
                entityGlowColour = { 1, 0, 0, 1 };

            memManager->writeMem<colours>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x04), entityGlowColour);
            memManager->writeMem<bool>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x24), true);
            memManager->writeMem<bool>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x25), false);
            //memManager->writeMem<bool>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x26), false);
        }
    }
}

