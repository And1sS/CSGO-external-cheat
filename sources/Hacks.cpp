#include "Hacks.h"

Hacks::Hacks(MemManager* memManager)
{
    this->memManager = memManager;

    glowObject = memManager->readMem<DWORD>(
        (LPCVOID)(memManager->getClientPanoramaDllAddress() + offsets::signatures::dwGlowObjectManager));
}

BaseEntity Hacks::getLocalPlayer()
{
    DWORD localPlayerAddr = memManager->readMem<DWORD>(LPCVOID(memManager->getClientPanoramaDllAddress()
        + offsets::signatures::dwLocalPlayer));
    return BaseEntity(memManager, localPlayerAddr);
}

void Hacks::loadEntityList()
{
    entityList.clear();
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        DWORD entityObjectPointer = memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwEntityList + i * struct_size::player_EntSize;
        BaseEntity entity(memManager, memManager->readMem<DWORD>((LPCVOID)entityObjectPointer));

        if (entity.isValid() != NULL)
        {
            entityList.push_back(entity);
        }
    }
}

void Hacks::printEntitiesInfo()
{
    BaseEntity localPlayer = getLocalPlayer();

    system("cls");
    std::cout << "debug mode" << std::endl;
    std::cout << "lp : " << std::hex << localPlayer.getBase() << std::endl;
    for (int i = 0; i < entityList.size(); i++)
    {
        std::cout << "entity #" << i << " ";
        entityList[i].printInfo();
    }
}

void Hacks::glowESP()
{
    BaseEntity localPlayer = getLocalPlayer();
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
            //memManager->writeMem<bool>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x26), f);
        }
    }
}

void Hacks::antiFlash()
{
    float duration = memManager->readMem<float>(LPCVOID(getLocalPlayer().getBase() + offsets::netvars::m_flFlashDuration));
    if (duration > 0)
    {
        memManager->writeMem<float>(LPVOID(getLocalPlayer().getBase() + offsets::netvars::m_flFlashDuration), 0);
    }
}

void Hacks::bunnyHop()
{
    BYTE flag = memManager->readMem<BYTE>(LPCVOID(getLocalPlayer().getBase() 
        + offsets::signatures::m_fFlags));
    if (GetAsyncKeyState(VK_SPACE) && flag & FL_ONGROUND)
    {
        memManager->writeMem<DWORD>(LPVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwForceJump), 6);
    }
}

void Hacks::triggerBot()
{
    uint32_t entityInCrosshairId = memManager->readMem<uint32_t>(LPCVOID(getLocalPlayer().getBase() +
        + offsets::netvars::m_iCrosshairId));
    DWORD entityInCrosshairPointer = memManager->getClientPanoramaDllAddress()
        + offsets::signatures::dwEntityList + (entityInCrosshairId - 1) * struct_size::player_EntSize;
    BaseEntity entityInCrosshair(memManager, memManager->readMem<DWORD>(LPCVOID(entityInCrosshairPointer)));

    if (entityInCrosshairId > 0 && entityInCrosshairId < 64 &&
        entityInCrosshair.getTeam() != getLocalPlayer().getTeam())
    {
        memManager->writeMem<uint32_t>(LPVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwForceAttack), 5);
        Sleep(20);
        memManager->writeMem<uint32_t>(LPVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwForceAttack), 4);
    }
}
