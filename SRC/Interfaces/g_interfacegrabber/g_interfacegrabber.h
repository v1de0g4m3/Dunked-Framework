#pragma once

class g_interfacegrabber
{
	typedef void* (*CreateInterfaceFn)(const char* p1, int* p2);
public:
	static void* getAddress(HMODULE hModule, const char* chInterface);
	static void CheckValidModules();
	static void dump();

	HMODULE hClient = nullptr;
	HMODULE hEngine = nullptr;
	HMODULE hVgui2 = nullptr;
	HMODULE hVguimatsurface = nullptr;
	HMODULE hVstdlib = nullptr;
	HMODULE hInputsystem = nullptr;
	HMODULE hLuashared = nullptr;
	HMODULE hGameui = nullptr;
	HMODULE hTier0 = nullptr;
};