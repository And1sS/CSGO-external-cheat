#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <cstdint>

#include "MemManager.h"
#include "Vec3.h"
#include "MemOffsets.h"

class BaseEntity
{
private:
    MemManager* memManager;
    DWORD base;

public:
    BaseEntity(MemManager* memManager, DWORD base);

    bool isValid();

    uint32_t getHealth();
    uint32_t getTeam();
    uint32_t getGlowIndex();

    DWORD getBase();

    Vec3 getOrigin();
};

