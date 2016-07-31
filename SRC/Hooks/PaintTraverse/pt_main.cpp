#include "../../sdk.h"

extern PaintTraverseFn oPaintTraverse;

void g_PaintTraverse::Paint()
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	// Paint funcs will go here
	g_Interfaces::surface->DrawFilledRect(25, 25, 250, 250);
	g_Interfaces::surface2->DrawTextA(2, 10, 10, 0, Color(255, 255, 255), "Dunked-Framework");
}

unsigned int iPaintID = 0;

void __fastcall g_PaintTraverse::Main(void* ecx, void* edx, unsigned int iPanel, bool bRepaint, bool bForce)
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	oPaintTraverse(ecx, edx, iPanel, bRepaint, bForce);

	auto chPanelClass = g_Interfaces::panel->GetName(iPanel);

	if (!iPaintID && strcmp(chPanelClass, "MatSystemTopPanel") == 0)
	{

		iPaintID = iPanel;
		return;
	}

	if (iPanel != iPaintID)
		return;

	Paint();
}

