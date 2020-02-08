#include "BaseEntity.h"

BaseEntity::BaseEntity(MemManager* memManager, DWORD base)
{
	this->memManager = memManager;
	this->base = base;
};

uint32_t BaseEntity::getHealth()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + memdump::netvars::m_iHealth));
};

uint32_t BaseEntity::getTeam()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + memdump::netvars::m_iTeamNum));
}

uint32_t BaseEntity::getGlowIndex()
{
	return memManager->readMem<uint32_t>(LPCVOID(base + memdump::netvars::m_iGlowIndex));
}

Vec3 BaseEntity::getOrigin()
{
	return memManager->readMem<Vec3>(LPCVOID(base + memdump::netvars::m_vecOrigin));
};

bool BaseEntity::isValid()
{
	return base != NULL;
}

DWORD BaseEntity::getBase()
{
	return base;
}