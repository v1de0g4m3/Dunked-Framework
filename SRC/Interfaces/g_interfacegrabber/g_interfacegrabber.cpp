#include "../../sdk.h"

void* g_interfacegrabber::getAddress(HMODULE hModule, const char* chInterface)
{
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

void g_interfacegrabber::CheckValidModules()
{
	using namespace g_Interfaces;

	g_utilList::console->Print(" Waiting for game");

	do
	{
		grab->hClient = GetModuleHandleA("client.dll");
		grab->hEngine = GetModuleHandleA("engine.dll");
		grab->hVgui2 = GetModuleHandleA("vgui2.dll");
		grab->hVguimatsurface = GetModuleHandleA("vguimatsurface.dll");
		grab->hVstdlib = GetModuleHandleA("vstdlib.dll");
		grab->hInputsystem = GetModuleHandleA("inputsystem.dll");
		grab->hLuashared = GetModuleHandleA("lua_shared.dll");
		grab->hGameui = GetModuleHandleA("gameui.dll");
		grab->hTier0 = GetModuleHandleA("tier0.dll");
		g_utilList::console->Print(".");
		Sleep(250);
	} while (grab->hClient == nullptr 
		|| grab->hEngine == nullptr 
		|| grab->hVgui2 == nullptr 
		|| grab->hVguimatsurface == nullptr 
		|| grab->hVstdlib == nullptr 
		|| grab->hInputsystem == nullptr
		|| grab->hLuashared == nullptr
		|| grab->hGameui == nullptr
		|| grab->hTier0 == nullptr);

	g_utilList::console->Print(" Game Started\n");
}

void g_interfacegrabber::dump()
{
	using namespace g_Interfaces;

	CheckValidModules();

	Sleep(1000);
	client = static_cast<g_chclient*>(grab->getAddress(grab->hClient, "VClient"));

	do
	{
		clientmode = **reinterpret_cast<void***>((*reinterpret_cast<DWORD**>(client))[10] + 0x5);
		globaldata = reinterpret_cast<g_globaldata*>(g_utilList::hook->dwFindPattern("client.dll", "\xA1\x00\x00\x00\x00\xD9\x40\x10\x56\x83\xEC\x08", "x????xxxxxxx", "globalddata"));
	} while (clientmode == nullptr || globaldata == nullptr);
	

	prediction = static_cast<g_prediction*>(grab->getAddress(grab->hClient, "VClientPrediction"));
	entlist = static_cast<g_cliententitylist*>(grab->getAddress(grab->hClient, "VClientEntityList"));
	gamemovement = static_cast<g_gamemovement*>(grab->getAddress(grab->hClient, "GameMovement"));

	engine = static_cast<g_engineclient*>(grab->getAddress(grab->hEngine, "VEngineClient"));
	trace = static_cast<g_EngineTrace*>(grab->getAddress(grab->hEngine, "EngineTraceClient"));
	modeldata = static_cast<g_modeldata*>(grab->getAddress(grab->hEngine, "VModelInfoClient"));
	debugoverlay = static_cast<g_debugoverlay*>(grab->getAddress(grab->hEngine, "VDebugOverlay"));

	surface = static_cast<g_surface*>(grab->getAddress(grab->hVguimatsurface, "VGUI_Surface"));

	panel = static_cast<g_panel*>(grab->getAddress(grab->hVgui2, "VGUI_Panel"));

	input = static_cast<g_input*>(grab->getAddress(grab->hInputsystem, "InputSystemVersion"));

	cvar = static_cast<g_cvar*>(grab->getAddress(grab->hVstdlib, "VEngineCvar"));

	luashared = static_cast<g_LuaShared*>(grab->getAddress(grab->hLuashared, "LUASHARED"));

	gameconsole = static_cast<g_gameconsole*>(grab->getAddress(grab->hGameui, "GameConsole"));
}

g_interfacegrabber* g_Interfaces::grab = new g_interfacegrabber;
void* g_Interfaces::clientmode;
g_gameconsole* g_Interfaces::gameconsole;

