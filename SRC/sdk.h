#pragma once

/*
****************************
      Dunked-Framework
****************************
*/

static const char* BUILDDATE = __DATE__;
static const char* BUILDTIME = __TIME__;
static const char* BUILDVERS = "0.2";

#define _CRT_SECURE_NO_WARNINGS
#define VC_EXTRALEAN
#define LUA state->luabase

using byte = unsigned char;

#pragma warning(push, 0) // Disables code I didn't write from showing up with errors
// Windows Includes
#include <Windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <process.h>
#include <string>
#include <sstream>
#include <Psapi.h>
#include <fstream>
#pragma warning(pop)

// Namespace
namespace Dunked
{
	extern unsigned int __stdcall Init(void*);
	extern void DeInit();
}

// Local Includes
// Valve Shit
#pragma warning(push, 0) // Disables code I didn't write from showing up with errors
#include "Valve/bspflags.h"
#include "Valve/dt_recv.h"
#pragma warning(pop)

// Utilities
#include "Utilities/g_utillist.h"

// Interfaces
#include "Interfaces/g_interfacelist.h"

// Hooks
#include "Hooks/g_hooklist.h"

// Lua Functions
#include "Lua Functions/g_luafuncs.h"

