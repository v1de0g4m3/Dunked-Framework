#include "../../sdk.h"

extern ClientModeFn oClientMode;

bool __fastcall g_ClientMode::Main(void* ecx, float input, CUserCmd* pCmd)
{
	oClientMode(ecx, input, pCmd);

	//pCmd->viewangles.x = rand() % 89;

	g_utilList::console->Print("%f\n", pCmd->viewangles.x);

	return false;
}
