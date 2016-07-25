#pragma once

/*
****************************
      Dunked-Framework
****************************
*/

static const char* BUILDDATE = __DATE__;
static const char* BUILDTIME = __TIME__;

#define _CRT_SECURE_NO_WARNINGS
#define VC_EXTRALEAN

using byte = unsigned char;

// Windows Includes
#include <Windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <process.h>
#include <string>
#include <Psapi.h>

// Namespace
namespace Dunked
{
	extern unsigned int __stdcall Init(void*);
	extern void DeInit();
}

// Local Includes
// Valve Shit
#include "Valve/bspflags.h"
#include "Valve/dt_recv.h"

// Utilities
#include "Utilities/g_utillist.h"

// CUserCmd
struct CUserCmd
{
	byte _pad1[4];
	float command_number;
	float tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	byte _pad2[12];
	int random_seed;
	__int16 mousedx;
	__int16 mousey;
	byte _pad3[288];
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd;
	unsigned int m_crc;
};

class CCMDInput
{
public:
	void*				pvftable;						//0x00
	bool				m_fTrackIRAvailable;			//0x04
	bool				m_fMouseInitialized;			//0x05
	bool				m_fMouseActive;					//0x06
	bool				m_fJoystickAdvancedInit;		//0x07
	char				pad_0x08[0x2C];					//0x08
	void*				m_pKeys;						//0x34
	char				pad_0x38[0x64];					//0x38
	bool				m_fCameraInterceptingMouse;		//0x9C
	bool				m_fCameraInThirdPerson;			//0x9D
	bool				m_fCameraMovingWithMouse;		//0x9E
	Vector				m_vecCameraOffset;				//0xA0
	bool				m_fCameraDistanceMove;			//0xAC
	int					m_nCameraOldX;					//0xB0
	int					m_nCameraOldY;					//0xB4
	int					m_nCameraX;						//0xB8
	int					m_nCameraY;						//0xBC
	bool				m_CameraIsOrthographic;			//0xC0
	Angle				m_angPreviousViewAngles;		//0xC4
	Angle				m_angPreviousViewAnglesTilt;	//0xD0
	float				m_flLastForwardMove;			//0xDC
	int					m_nClearInputState;				//0xE0
	char				pad_0xE4[0x8];					//0xE4
	CUserCmd*			m_pCommands;					//0xEC
	CVerifiedUserCmd*	m_pVerifiedCommands;			//0xF0
};

// Interfaces
#include "Interfaces/g_interfacelist.h"

