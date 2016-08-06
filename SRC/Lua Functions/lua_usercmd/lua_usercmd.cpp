#include "../../sdk.h"

void lua_usercmd::Initialize(g_LuaInterface* menustate)
{
	// CUserCmd Shit
	menustate->CreateMetaTableType("CUserCmd", TYPE_USERCMD);
	g_LuaObject* pCmdMeta = menustate->GetMetaTableObject("CUserCmd", TYPE_USERCMD);

	menustate->PushCFunction(lua_metatables::__eq);
	menustate->SetField(-2, "__eq");

	menustate->PushLuaObject(pCmdMeta);
	menustate->SetField(-2, "__index");

	menustate->PushLuaObject(pCmdMeta);
	menustate->SetField(-2, "__newindex");

	menustate->PushCFunction(lua_metatables::__tostring);
	menustate->SetField(-2, "__tostring");

	auto ref = menustate->ReferenceCreate();
	menustate->ReferencePush(ref);

	// functions
	menustate->PushCFunction(GetCommandNumber);
	menustate->SetField(-2, "GetCommandNumber");

	menustate->ReferenceFree(ref);

	menustate->Pop(3);
}

int lua_usercmd::GetCommandNumber(lua_State* state)
{
	auto pCmd = _G::pCmd;
	if (!pCmd)
		return 1;

	LUA->PushNumber(pCmd->command_number);
	return 1;
}
