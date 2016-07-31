#include "../../sdk.h"

CUserCmd* g_input::GetUserCmd(int sequence)
{
	typedef CUserCmd*(__thiscall* vFn)(void*, int);
	return vfunc<vFn>(this, 8)(this, sequence);
}

g_input* g_Interfaces::input = new g_input;

