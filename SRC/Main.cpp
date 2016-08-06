/*
	****************************
	      Dunked-Framework
	****************************
	Project Started: 23/07/2016
	Project By: Phage

	Credits to:
		Ley - For starting the original project
		Herp Derpinstine - For putting up with constant questions and my general retardation
		Mythik - For giving me the idea to write my own
		Senator@cheater.team - Tons of help, collabed with many many cheats, many more in the future
		Snipwnage - Color, Vector, Angle classes (I got lazy)
		Daz - Tons of source engine knowledge, small optomizations
*/
#include "sdk.h"

ClientModeFn oClientMode;
PaintTraverseFn oPaintTraverse;

unsigned int __stdcall Dunked::Init(void*)
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	g_utilList::console->Create("Dunked-Framework");
	g_utilList::console->Visible(true);

	g_utilList::file->DirCreate("C:\\Dunked");
	g_utilList::file->DirCreate("C:\\Dunked\\Log");

	g_utilList::console->centerPrint("*****************************************************************************\n");
	g_utilList::console->centerPrint("Dunked-Framework\n");
	g_utilList::console->centerPrint(" By Phage\n");
	g_utilList::console->centerPrint("*****************************************************************************\n");
	g_utilList::console->Print(" Build Date: %s\n", BUILDDATE);
	g_utilList::console->Print(" Build Time: %s\n", BUILDTIME);

	g_Interfaces::grab->dump();
	g_utilList::hook->HookAll();
	g_utilList::offsets->DumpNetvars();
	g_LuaInit::InitalizeMenuState();

	Beep(512, 1000);
	return 1;
}

void Dunked::DeInit()
{
	// UtilList deallocate
	delete g_utilList::exception;
	delete g_utilList::console;
	delete g_utilList::hook;
	delete g_utilList::netvar;
	delete g_utilList::offsets;
	delete g_utilList::math;

	// Interface deallocate
	delete g_Interfaces::client;
	delete g_Interfaces::globaldata;
	delete g_Interfaces::entlist;
	delete g_Interfaces::clientmode;
	delete g_Interfaces::cvar;
	delete g_Interfaces::cvarsearch;
	delete g_Interfaces::debugoverlay;
	delete g_Interfaces::engine;
	delete g_Interfaces::gameconsole;
	delete g_Interfaces::input;
	delete g_Interfaces::grab;
	delete g_Interfaces::lua;
	delete g_Interfaces::panel;
	delete g_Interfaces::modeldata;
	delete g_Interfaces::gamemovement;
	delete g_Interfaces::prediction;
	delete g_Interfaces::movehelper;
	delete g_Interfaces::surface;
	delete g_Interfaces::surface2;
	delete g_Interfaces::trace;
}

void DLLMainInit(HMODULE hModule)
{
	void* pThread;
	unsigned int id;

	_G::hDLLModule = hModule;
	SetUnhandledExceptionFilter(g_utilList::exception->unhandledExceptionFilter);

	do
	{
		pThread = reinterpret_cast<void*>(_beginthreadex(nullptr, NULL, Dunked::Init, nullptr, 0, &id));
	} while (pThread == nullptr);

	DisableThreadLibraryCalls(hModule);
	CloseHandle(pThread);
}

extern "C" int __stdcall DllMain(HMODULE hModule, DWORD dwReason, void*)
{	
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DLLMainInit(hModule);
		break;

	case DLL_PROCESS_DETACH:
		Dunked::DeInit();
		break;
	}

	return TRUE;
}
