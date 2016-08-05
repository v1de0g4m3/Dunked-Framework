#pragma once

class g_interfacegrabber
{
	typedef void* (*CreateInterfaceFn)(const char* p1, int* p2);
	HMODULE hClient = nullptr;
	HMODULE hEngine = nullptr;
	HMODULE hVgui2 = nullptr;
	HMODULE hVguimatsurface = nullptr;
	HMODULE hVstdlib = nullptr;
	HMODULE hInputsystem = nullptr;
public:
	static void* getAddress(HMODULE hModule, const char* chInterface);
	static void CheckValidModules();
	static void dump();
};