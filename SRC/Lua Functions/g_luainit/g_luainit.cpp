#include "../../sdk.h"

void g_LuaInit::InitalizeMenuState()
{
	g_Interfaces::lua->InitLuaShared(g_Interfaces::luashared);

	auto ILuaMenuState = g_Interfaces::lua->GetMenuState();

	ILuaMenuState->PushSpecial(SPECIAL_GLOB);
	ILuaMenuState->CreateTable();

	//CUserCmd
	lua_usercmd::Initialize(ILuaMenuState);

	g_Interfaces::lua->RunCode(ILuaMenuState, std::string("local pmeta = FindMetaTable('Player') for k,v in pairs(FindMetaTable('Entity')) do if(not pmeta[k]) then pmeta[k] = v end end"), "[C]");
}
