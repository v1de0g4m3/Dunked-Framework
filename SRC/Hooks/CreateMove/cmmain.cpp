#include "../../sdk.h"

extern ClientModeFn oClientMode;

bool g_ClientMode::Verify(CUserCmd* pCmd) 
{
	return (pCmd != nullptr) && (fabs(pCmd->command_number) > DBL_EPSILON);
}

bool __fastcall g_ClientMode::Main(void* edx, float input, CUserCmd* pCmd)
{
	oClientMode(edx, input, pCmd);

	if (!Verify(pCmd))
		return false;

	g_utilList::console->Print("%f\n", pCmd->viewangles.x);

	return false;
}
