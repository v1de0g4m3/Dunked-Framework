#include "../../sdk.h"

bool g_lua::InitLuaShared(g_LuaShared* luashared)
{
	auto hLuaShared = g_Interfaces::grab->hLuashared;

	luaL_loadbufferx = reinterpret_cast<int(*)(void*, const char*, size_t, const char*, void*)>(GetProcAddress(hLuaShared, "luaL_loadbufferx"));
	lua_pcall = reinterpret_cast<int(*)(void*, int, int, int)>(GetProcAddress(hLuaShared, "lua_pcall"));
	lua_settop = reinterpret_cast<void(*)(void*, int)>(GetProcAddress(hLuaShared, "lua_settop"));
	lua_gettop = reinterpret_cast<int(*)(void*)>(GetProcAddress(hLuaShared, "lua_gettop"));
	lua_tolstring = reinterpret_cast<const char*(*)(void*, int, int)>(GetProcAddress(hLuaShared, "lua_tolstring"));
	lua_replace = reinterpret_cast<void(*)(void *L, int index)>(GetProcAddress(hLuaShared, "lua_replace"));
	lua_remove = reinterpret_cast<void(*)(void *L, int index)>(GetProcAddress(hLuaShared, "lua_remove"));
	lua_xmove = reinterpret_cast<void(*)(void *from, void* to, int n)>(GetProcAddress(hLuaShared, "lua_xmove"));
	lua_type = reinterpret_cast<int(*)(void*L, int index)>(GetProcAddress(hLuaShared, "lua_type"));
	luaL_newstate = reinterpret_cast<void*(*)()>(GetProcAddress(hLuaShared, "luaL_newstate"));

	if (!luaL_loadbufferx || !lua_pcall || !lua_settop || !lua_gettop || !lua_tolstring || !lua_replace || !lua_remove || !lua_type || !luaL_newstate || !lua_xmove)
	{
		g_utilList::console->Print("LuaShared initialization failed.\n");
		return false;
	}
	lua_shared = luashared;

	return true;
}

g_LuaInterface* g_lua::GetMenuState() const
{
	return lua_shared->GetLuaInterface(LUA_MENU);
}

g_LuaInterface* g_lua::GetClientState() const
{
	return lua_shared->GetLuaInterface(LUA_CLIENT);;
}

g_LuaInterface* g_lua::RetLuaState(g_LuaInterface* garrystate)
{
	return *reinterpret_cast<g_LuaInterface**>(reinterpret_cast<char*>(garrystate) + 0x4);
}

std::string g_lua::RunCode(g_LuaInterface* state, std::string code, const char* name) const
{
	std::string rtn("");

	g_LuaInterface* realstate = RetLuaState(state);

	auto iError = luaL_loadbufferx(realstate, code.c_str(), code.length(), name, nullptr);

	if (iError)
	{
		auto szError = lua_tolstring(realstate, -1, 0);

		lua_settop(realstate, -2);
		return std::string(szError);
	}

	if (lua_pcall(realstate, 0, -1, 0))
	{
		lua_settop(realstate, -2);
		return rtn;
	}

	return rtn;
}

g_lua* g_Interfaces::lua = new g_lua;
g_LuaShared* g_Interfaces::luashared;