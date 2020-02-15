#include "Hacks.h"

Hacks::Hacks(MemManager* memManager) : memManager(memManager) {}

BaseEntity Hacks::getLocalPlayer()
{
    DWORD localPlayerAddr = memManager->readMem<DWORD>(LPCVOID(memManager->getClientPanoramaDllAddress()
        + offsets::signatures::dwLocalPlayer));
//    DWORD entityListAddr = memManager->readMem<DWORD>(LPCVOID(memManager->getClientPanoramaDllAddress()
//        + offsets::signatures::dwEntityList));
//    uint32_t id = (localPlayerAddr - entityListAddr) / 0x10;

    return BaseEntity(memManager, localPlayerAddr, 0);
}

DWORD Hacks::getGlowObjectManager()
{
    return memManager->readMem<DWORD>(
        LPCVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwGlowObjectManager));
}

void Hacks::loadEntityList()
{
    entityList.clear();
    for (auto i = 0; i < MAX_ENTITIES; i++)
    {
        DWORD entityObjectPointer = memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwEntityList + i * struct_size::player_EntSize;                      // entityPointer = "client_panorama.dll" + entityListPointer + i * 0x10
        BaseEntity entity(memManager, memManager->readMem<DWORD>((LPCVOID)entityObjectPointer),
                          (uint32_t)i);                                                                            // entityAddress = readMemory(entityPointer)

        if (entity.isValid())
        {
            entityList.push_back(entity);
        }
    }
}

void Hacks::printEntitiesInfo()
{
    BaseEntity localPlayer = getLocalPlayer();

    std::cout << "debug mode" << std::endl;
    std::cout << "local player : " << std::hex << localPlayer.getBase() << std::endl;

    for (auto i = 0; i < entityList.size(); i++)
    {
        std::cout << "entity #" << i << " ";
        entityList[i].printInfo();
    }
}

void Hacks::glowESP()
{
    if (!glowEspEnabled)
    {
        return;
    }

    BaseEntity localPlayer = getLocalPlayer();
    for (auto i = 0; i < entityList.size(); i++)
    {
        if (entityList[i].isValid() != NULL && entityList[i].getBase() != localPlayer.getBase())
        {
            colours entityGlowColour;
            if (entityList[i].getTeam() == localPlayer.getTeam())
            {
                if (!glowTeamMates)
                {
                    continue;
                }
                entityGlowColour = teammateColours;
            }

            else
            {
                if (!glowEnemies)
                {
                    continue;
                }
                entityGlowColour = enemyColours;

//                if ((entityList[i].getSpottedByMask() & (1 << localPlayer.getId())) != 0)
//                    entityGlowColour = { 1, 1, 1, 1 };
            }

            memManager->writeMem<colours>(LPVOID(getGlowObjectManager() + (entityList[i].getGlowIndex() * 0x38) + 0x04),
                                          entityGlowColour); // Writing rgba
            memManager->writeMem<bool>(LPVOID(getGlowObjectManager() + (entityList[i].getGlowIndex() * 0x38) + 0x24), true);                // Enabling glow
            memManager->writeMem<bool>(LPVOID(getGlowObjectManager() + (entityList[i].getGlowIndex() * 0x38) + 0x25), false);               // Disabling glow shape filling
            //memManager->writeMem<bool>(LPVOID(glowObject + (entityList[i].getGlowIndex() * 0x38) + 0x26), f);
        }
    }
}

void Hacks::antiFlash()
{
    if (!antiflashEnabled)
    {
        return;
    }

    float duration = memManager->readMem<float>(LPCVOID(getLocalPlayer().getBase() + offsets::netvars::m_flFlashDuration));
    if (duration > 0)
    {
        memManager->writeMem<float>(LPVOID(getLocalPlayer().getBase() + offsets::netvars::m_flFlashDuration), 0);               // flashDurationAddress = localPlayerAddress + flashDuration offset
    }
}

void Hacks::bunnyHop()
{
    if (!bunnyhopEnabled)
    {
        return;
    }

    BYTE flag = memManager->readMem<BYTE>(LPCVOID(getLocalPlayer().getBase() 
        + offsets::signatures::m_fFlags));
    if (GetAsyncKeyState(VK_SPACE) && (flag & FL_ONGROUND))
    {
        memManager->writeMem<DWORD>(LPVOID(memManager->getClientPanoramaDllAddress()                                            // forceJumpValue = "client_panorama.dll" + forceJump offset
            + offsets::signatures::dwForceJump), 6);                                                                            // 6 - Jump
    }
}

void Hacks::triggerBot()
{
    if (!triggerBotEnabled)
    {
        return;
    }

    uint32_t entityInCrosshairId = memManager->readMem<uint32_t>(LPCVOID(getLocalPlayer().getBase() +
        + offsets::netvars::m_iCrosshairId));
    DWORD entityInCrosshairPointer = memManager->getClientPanoramaDllAddress()
        + offsets::signatures::dwEntityList + (entityInCrosshairId - 1) * struct_size::player_EntSize;
    BaseEntity entityInCrosshair(memManager, memManager->readMem<DWORD>(LPCVOID(entityInCrosshairPointer)),
                                 entityInCrosshairId);

    if (entityInCrosshairId > 0 && entityInCrosshairId < MAX_ENTITIES &&
        entityInCrosshair.getTeam() != getLocalPlayer().getTeam())
    {
        memManager->writeMem<uint32_t>(LPVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwForceAttack), 5);
        Sleep(20);
        memManager->writeMem<uint32_t>(LPVOID(memManager->getClientPanoramaDllAddress()
            + offsets::signatures::dwForceAttack), 4);
    }
}

void Hacks::setGlowEsp(bool enabled)
{
    glowEspEnabled = enabled;
}

void Hacks::setBunnyHop(bool enabled)
{
    bunnyhopEnabled = enabled;
}

void Hacks::setAntiflash(bool enabled)
{
    antiflashEnabled = enabled;
}

void Hacks::setTriggerBot(bool enabled)
{
    triggerBotEnabled = enabled;
}

void Hacks::setTeamMatesGlowing(bool enabled)
{
    glowTeamMates = enabled;
}

void Hacks::setEnemiesGlowing(bool enabled)
{
    glowEnemies = enabled;
}

void Hacks::setTeamMateGlowingColours(colours colours)
{
    teammateColours = colours;
}

void Hacks::setEnemyGlowingColours(colours colours)
{
    enemyColours = colours;
}
