#include "../../sdk.h"

void g_LuaInit::InitalizeMenuState()
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	DisplayWelcomeMessage();

	g_Interfaces::lua->InitLuaShared(g_Interfaces::luashared);

	auto ILuaMenuState = g_Interfaces::lua->GetMenuState();

	ILuaMenuState->PushSpecial(SPECIAL_GLOB);
	ILuaMenuState->CreateTable();

	//CUserCmd
	lua_usercmd::Initialize(ILuaMenuState);

	g_Interfaces::lua->RunCode(ILuaMenuState, std::string("local pmeta = FindMetaTable('Player') for k,v in pairs(FindMetaTable('Entity')) do if(not pmeta[k]) then pmeta[k] = v end end"), "[C]");
}

void g_LuaInit::DisplayWelcomeMessage()
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	g_Interfaces::gameconsole->Activate();
	g_Interfaces::gameconsole->Clear();

	g_utilList::console->ConsolePrint(R"###(__/\\\\\\\\\\\\_____________________________________________________________________/\\\__________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(__\/\\\////////\\\_______________________________/\\\_______________________________\/\\\_________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(___\/\\\______\//\\\_____________________________\/\\\_______________________________\/\\\________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(____\/\\\_______\/\\\__/\\\____/\\\__/\\/\\\\\\___\/\\\\\\\\________/\\\\\\\\_________\/\\\_______)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_____\/\\\_______\/\\\_\/\\\___\/\\\_\/\\\////\\\__\/\\\////\\\____/\\\/////\\\___/\\\\\\\\\______)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(______\/\\\_______\/\\\_\/\\\___\/\\\_\/\\\__\//\\\_\/\\\\\\\\/____/\\\\\\\\\\\___/\\\////\\\_____)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_______\/\\\_______/\\\__\/\\\___\/\\\_\/\\\___\/\\\_\/\\\///\\\___\//\\///////___\/\\\__\/\\\____)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(________\/\\\\\\\\\\\\/___\//\\\\\\\\\__\/\\\___\/\\\_\/\\\_\///\\\__\//\\\\\\\\\\_\//\\\\\\\/\\__)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_________\////////////______\/////////___\///____\///__\///____\///____\//////////___\///////\//__)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	

	
	g_utilList::console->ConsolePrint("\n", false);

	std::stringstream Versinfo;
	Versinfo << "Dunked-Framework Version " << BUILDVERS << " Initialized, Built on " << BUILDDATE << " at " << BUILDTIME << ".\n";
	g_utilList::console->ConsolePrint(Versinfo.str().c_str(), false);

	g_Interfaces::engine->ClientCmd("help");
}
