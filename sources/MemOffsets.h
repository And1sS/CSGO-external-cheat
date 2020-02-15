#pragma once

#include <cstddef>

// 2020-02-07 18:43:58.258902800 UTC

#define	FL_ONGROUND				(1 << 0)	// At rest / on the ground
#define FL_DUCKING				(1 << 1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1 << 2)	// player jumping out of water
#define FL_ONTRAIN				(1 << 3)    // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1 << 4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1 << 5)    // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1 << 6)    // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1 << 7)	// Is a player
#define FL_FAKECLIENT			(1 << 8)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1 << 9)	// In water

namespace struct_size
{
	constexpr ::std::ptrdiff_t player_EntSize = 0x10;
}

namespace offsets
{
	namespace netvars 
	{
		constexpr ::std::ptrdiff_t m_iHealth = 0x100;				// Health offset from entity address
		constexpr ::std::ptrdiff_t m_vecOrigin = 0x138;				// Origin offset from entity address
        constexpr ::std::ptrdiff_t m_flFlashDuration = 0xA410;		// Flash duration offset from local player address
		constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;				// Team number offset from entity address 2 - T, 3 - CT
		constexpr ::std::ptrdiff_t m_iGlowIndex = 0xA428;			// Glow index offset from entity address
		constexpr ::std::ptrdiff_t m_iCrosshairId = 0xB3D4;
        constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x980;
	} 

	namespace signatures
	{
        constexpr ::std::ptrdiff_t dwLocalPlayer = 0xD28B74;
		constexpr ::std::ptrdiff_t dwClientState_GetLocalPlayer = 0x180;
        constexpr ::std::ptrdiff_t dwGlowObjectManager = 0x527DFA0;
		constexpr ::std::ptrdiff_t dwClientState_State = 0x108;
        constexpr ::std::ptrdiff_t dwEntityList = 0x4D3C7BC;
        constexpr ::std::ptrdiff_t dwClientState = 0x588D9C;
        constexpr ::std::ptrdiff_t dwForceAttack = 0x316DD80;
        constexpr ::std::ptrdiff_t dwForceJump = 0x51E0004;
		constexpr ::std::ptrdiff_t m_fFlags = 0x104;
	}
}
