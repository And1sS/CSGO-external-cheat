#include "BaseEntity.h"

BaseEntity::BaseEntity(MemManager* memManager, DWORD base, uint32_t id)
    : memManager(memManager), base(base), id(id) {};

uint32_t BaseEntity::getHealth()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + offsets::netvars::m_iHealth));
};

uint32_t BaseEntity::getTeam()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + offsets::netvars::m_iTeamNum));
}

uint32_t BaseEntity::getGlowIndex()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + offsets::netvars::m_iGlowIndex));
}

Vec3 BaseEntity::getOrigin()
{
	return memManager->readMem<Vec3>(LPCVOID(base + offsets::netvars::m_vecOrigin));
}

uint32_t BaseEntity::getSpottedByMask()
{
   return memManager->readMem<uint32_t>(LPCVOID(base + offsets::netvars::m_bSpottedByMask));
}

bool BaseEntity::isValid()
{
	return base != NULL;
}
