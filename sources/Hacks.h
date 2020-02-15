#pragma once

#include <vector>
#include <iostream>

#include "MemManager.h"
#include "BaseEntity.h"

#define MAX_ENTITIES 64

struct colours
{
    float r, g, b, a;
};

class Hacks
{
private:
    bool glowTeamMates = false;
    bool glowEnemies = false;
    bool glowEspEnabled = false;
    bool triggerBotEnabled = false;
    unsigned char _junk[17];                            // Junk bytes to renew signatures
    bool bunnyhopEnabled = false;
    bool antiflashEnabled = false;

	MemManager* memManager;

    unsigned char _junk1[133];                          // Junk bytes to renew signatures

    std::vector<BaseEntity> entityList;

    colours enemyColours = { 1, 0, 0, 1 };              // Green colour
    unsigned char _junk2[17];                          // Junk bytes to renew signatures
    colours teammateColours = { 0, 1, 0, 1 };           // Red colour

    DWORD getGlowObjectManager();

public:
	Hacks(MemManager* memManager);

	BaseEntity getLocalPlayer();

	void loadEntityList();

	void printEntitiesInfo();

	void glowESP();
	void antiFlash();
	void bunnyHop();
	void triggerBot();

    void setGlowEsp(bool enabled);
    void setAntiflash(bool enabled);
    void setBunnyHop(bool enabled);
    void setTriggerBot(bool enabled);
    void setEnemiesGlowing(bool enabled);
    void setTeamMatesGlowing(bool enabled);

    void setEnemyGlowingColours(colours colours);
    void setTeamMateGlowingColours(colours colours);
};

