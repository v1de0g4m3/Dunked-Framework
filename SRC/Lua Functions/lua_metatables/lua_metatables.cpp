#include "../../sdk.h"

int lua_metatables::__eq(lua_State* state)
{
	if (!LUA->IsType(1, TYPE_USERDATA) || !LUA->IsType(2, TYPE_USERDATA))
	{
		LUA->PushBool(false);
		return 1;
	}

	UserData* ud = LUA->GetUserdata(1);
	if (!ud)
	{
		LUA->PushBool(false);
		return 1;
	}

	UserData* ud2 = LUA->GetUserdata(2);
	if (!ud2)
	{
		LUA->PushBool(false);
		return 1;
	}

	if (ud->data == ud2->data)
	{
		LUA->PushBool(true);
		return 1;
	}

	LUA->PushBool(false);
	return 1;
}

int lua_metatables::__tostring(lua_State * state)
{
	if (!state || !LUA->IsType(1, TYPE_USERDATA))
		return 1;

	auto pEnt = static_cast<CBaseEntity*>(LUA->GetUserdata(1)->data);

	if (!pEnt)
		return 1;

	char ret[64];

	sprintf(ret, "Data [%s]", reinterpret_cast<char*>(pEnt));
	LUA->PushString(ret);

	return 1;
}
