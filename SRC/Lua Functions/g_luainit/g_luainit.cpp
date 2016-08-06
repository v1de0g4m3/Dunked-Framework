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

	std::string code;
	g_utilList::file->FileRead("C://Dunked//dunked.lua", code);
	
	if (!code.empty())
	{
		g_utilList::console->Print(code + "\n");
		g_Interfaces::lua->RunCode(ILuaMenuState, code, "[C]");
		g_utilList::console->Print("Lua Ran!\n");
	}
}

void g_LuaInit::DisplayWelcomeMessage()
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	g_Interfaces::gameconsole->Activate();
	g_Interfaces::gameconsole->Clear();

	g_utilList::console->ConsolePrint(R"###(___________/\\\\\\\\\\\\_____________________________________________________________________/\\\____________________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(___________\/\\\////////\\\_______________________________/\\\_______________________________\/\\\___________________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(____________\/\\\______\//\\\_____________________________\/\\\_______________________________\/\\\__________________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_____________\/\\\_______\/\\\__/\\\____/\\\__/\\/\\\\\\___\/\\\\\\\\________/\\\\\\\\_________\/\\\_________________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(______________\/\\\_______\/\\\_\/\\\___\/\\\_\/\\\////\\\__\/\\\////\\\____/\\\/////\\\___/\\\\\\\\\________________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_______________\/\\\_______\/\\\_\/\\\___\/\\\_\/\\\__\//\\\_\/\\\\\\\\/____/\\\\\\\\\\\___/\\\////\\\_______________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(________________\/\\\_______/\\\__\/\\\___\/\\\_\/\\\___\/\\\_\/\\\///\\\___\//\\///////___\/\\\__\/\\\______________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(_________________\/\\\\\\\\\\\\/___\//\\\\\\\\\__\/\\\___\/\\\_\/\\\_\///\\\__\//\\\\\\\\\\_\//\\\\\\\/\\____________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	g_utilList::console->ConsolePrint(R"###(__________________\////////////______\/////////___\///____\///__\///____\///____\//////////___\///////\//____________)###", true);
	g_utilList::console->ConsolePrint("\n", false);
	
	g_utilList::console->ConsolePrint("\n", false);

	std::stringstream Versinfo;
	Versinfo << "Dunked-Framework Version " << BUILDVERS << " Initialized, Built on " << BUILDDATE << " at " << BUILDTIME << ".\n";
	g_utilList::console->ConsolePrint(Versinfo.str().c_str(), false);

	g_Interfaces::engine->ClientCmd("help");
}
