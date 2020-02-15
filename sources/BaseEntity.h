#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <cstdint>
#include <iostream>

#include "MemManager.h"
#include "Vec3.h"
#include "MemOffsets.h"

class BaseEntity
{
private:
    MemManager* memManager;
    unsigned char _junk[13];
    DWORD base;
    uint32_t id;

public:
    BaseEntity(MemManager* memManager, DWORD base, uint32_t id);

    bool isValid();

    uint32_t getHealth();
    uint32_t getTeam();
    uint32_t getGlowIndex();

    DWORD getBase();

    uint32_t getId();

    Vec3 getOrigin();

    void printInfo();

    uint32_t getSpottedByMask();
};

inline DWORD BaseEntity::getBase()
{
    return base;
}

inline uint32_t BaseEntity::getId()
{
    return id;
}

inline void BaseEntity::printInfo()
{
    std::cout
        << "health address: "		<< std::hex << getBase() + offsets::netvars::m_iHealth
        << " health: "				<< std::dec << getHealth()
        << " x: "					<< getOrigin().getX()
        << " y: "					<< getOrigin().getY()
        << " z: "					<< getOrigin().getZ()
        << " team: : "				<< (getTeam() == 2 ? "T" : "CT")
        << std::endl << std::endl << std::endl;
}
