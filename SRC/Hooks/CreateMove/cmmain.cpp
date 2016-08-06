#include "../../sdk.h"

extern ClientModeFn oClientMode;

bool __fastcall g_ClientMode::Main(void* ecx, void* edx, float flInputSampleTime, CUserCmd* pCmd)
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	oClientMode(ecx, edx, flInputSampleTime, pCmd);

	_G::pCmd = pCmd;

	return false;
}
