#include "../../sdk.h"

void* g_interfacegrabber::getAddress(const char* chModule, const char* chInterface)
{
	HMODULE hModule;

	do
	{
		hModule = GetModuleHandleA(chModule);
		Sleep(50);
	} while (hModule == nullptr);

	char chInterfaceName[1024];
	chInterfaceName[0] = '\0';

	g_utilList::console->Print(" Dumping Interface %s... ", chInterface);
	auto InterfaceFn = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hModule, "CreateInterface"));

	for (auto i = 100; i > 0; i--)
	{
		sprintf(chInterfaceName, "%s%03i", chInterface, i);

		auto finalFn = InterfaceFn(chInterfaceName, nullptr);

		if (finalFn)
		{
			g_utilList::console->Print("(");
			g_utilList::console->Print((i < 10 ? "0%i" : "%i"), i);
			g_utilList::console->Print(",");
			g_utilList::console->Print(" 0x%X", finalFn);
			g_utilList::console->Print(")\n");
			return finalFn;
		}
	}

	g_utilList::console->Print("Can't Find Address!\n");
	return nullptr;
}

void g_interfacegrabber::dump()
{
	using namespace g_Interfaces;

	g_utilList::console->Print(" Waiting for game");
	while (!GetModuleHandleA("client.dll") 
		|| !GetModuleHandleA("engine.dll") 
		|| !GetModuleHandleA("vgui2.dll") 
		|| !GetModuleHandleA("vguimatsurface.dll")
		|| !GetModuleHandleA("vstdlib.dll")
		|| !GetModuleHandleA("inputsystem.dll"))
	{
		g_utilList::console->Print(".");
		Sleep(500);
	}
	g_utilList::console->Print(" Game Started\n");

	Sleep(1000);
	client = static_cast<g_chclient*>(grab->getAddress("client.dll", "VClient"));

	do
	{
		clientmode = **reinterpret_cast<void***>((*reinterpret_cast<DWORD**>(client))[10] + 0x5);
		globaldata = reinterpret_cast<g_globaldata*>(g_utilList::hook->dwFindPattern("client.dll", "\xA1\x00\x00\x00\x00\xD9\x40\x10\x56\x83\xEC\x08", "x????xxxxxxx", "globalddata"));
	} while (clientmode == nullptr || globaldata == nullptr);
	

	prediction = static_cast<g_prediction*>(grab->getAddress("client.dll", "VClientPrediction"));
	entlist = static_cast<g_cliententitylist*>(grab->getAddress("client.dll", "VClientEntityList"));
	gamemovement = static_cast<g_gamemovement*>(grab->getAddress("client.dll", "GameMovement"));

	engine = static_cast<g_engineclient*>(grab->getAddress("engine.dll", "VEngineClient"));
	trace = static_cast<g_EngineTrace*>(grab->getAddress("engine.dll", "EngineTraceClient"));
	modeldata = static_cast<g_modeldata*>(grab->getAddress("engine.dll", "VModelInfoClient"));
	debugoverlay = static_cast<g_debugoverlay*>(grab->getAddress("engine.dll", "VDebugOverlay"));

	surface = static_cast<g_surface*>(grab->getAddress("vguimatsurface.dll", "VGUI_Surface"));
	panel = static_cast<g_panel*>(grab->getAddress("vgui2.dll", "VGUI_Panel"));
	input = static_cast<g_input*>(grab->getAddress("inputsystem.dll", "InputSystemVersion"));
	cvar = static_cast<g_cvar*>(grab->getAddress("vstdlib.dll", "VEngineCvar"));	
}

g_interfacegrabber* g_Interfaces::grab = new g_interfacegrabber;
void* g_Interfaces::clientmode;

