#include "BaseEntity.h"

BaseEntity::BaseEntity(MemManager* memManager, DWORD base)
{
	this->memManager = memManager;
	this->base = base;
};

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
void BaseEntity::printInfo()
{
	std::cout << "health address: " << std::hex << getBase() + offsets::netvars::m_iHealth
		<< " health: " << std::dec << getHealth()
		<< " x: " << getOrigin().getX()
		<< " y: " << getOrigin().getY()
		<< " z: " << getOrigin().getZ()
		<< " team: : " << (getTeam() == 2 ? "T" : "CT")
		<< std::endl << std::endl << std::endl;
}

bool BaseEntity::isValid()
{
	return base != NULL;
}

DWORD BaseEntity::getBase()
{
	return base;
}