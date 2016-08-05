#pragma once

/*
****************************
      Dunked-Framework
****************************
*/

class Angle;
static const char* BUILDDATE = __DATE__;
static const char* BUILDTIME = __TIME__;

#define _CRT_SECURE_NO_WARNINGS
#define VC_EXTRALEAN
#define LUA state->luabase

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

// Interfaces
#include "Interfaces/g_interfacelist.h"

// Hooks
#include "Hooks/g_hooklist.h"

// Lua Functions
#include "Lua Functions/g_luafuncs.h"

