#pragma once

#include <vector>
#include <iostream>

#include "MemManager.h"
#include "BaseEntity.h"

#define MAX_ENTITIES 64

class Hacks
{
private:
	MemManager* memManager;
	DWORD glowObject;

	std::vector<BaseEntity> entityList;

	struct colours
	{
		float r, g, b, a;
	};

public:
	Hacks(MemManager* memManager);

	BaseEntity getLocalPlayer();

	void loadEntityList();

	void printEntitiesInfo();

	void glowESP();
	void antiFlash();
	void bunnyHop();
	void triggerBot();
};

