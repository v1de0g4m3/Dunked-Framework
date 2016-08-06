#include "../../sdk.h"

void g_surface::DrawSetColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int, int, int);
	vfunc<vFuncFn>(this, 11)(this, r, g, b, a);
}

void g_surface::DrawFilledRect(int x, int y, int w, int h)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int, int, int);
	vfunc<vFuncFn>(this, 12)(this, x, y, w + x, h + y); // add x to w and y to h to normalize
}

void g_surface::DrawOutlinedRect(int x, int y, int w, int h)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int, int, int);
	vfunc<vFuncFn>(this, 14)(this, x, y, w + x, h + y); // add x to w and y to h to normalize
}

void g_surface::DrawLine(int x, int y, int w, int h)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int, int, int);
	vfunc<vFuncFn>(this, 15)(this, x, y, w, h);
}

void g_surface::DrawSetTextFont(unsigned long eFont)
{
	typedef void(__thiscall* vFuncFn)(void*, unsigned long);
	return vfunc<vFuncFn>(this, 17)(this, eFont);
}

void g_surface::DrawSetTextColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int, int, int);
	return vfunc<vFuncFn>(this, 19)(this, r, g, b, a);
}

void g_surface::DrawSetTextPos(int x, int y)
{
	typedef void(__thiscall* vFuncFn)(void*, int, int);
	vfunc<vFuncFn>(this, 20)(this, x, y);
}

void g_surface::DrawPrintText(const wchar_t* chText, int iSize)
{
	typedef void(__thiscall* vFuncFn)(void*, const wchar_t*, int, int);
	return vfunc<vFuncFn>(this, 22)(this, chText, iSize, 0);
}

unsigned long g_surface::CreateFonts()
{
	typedef unsigned long(__thiscall* vFuncFn)(void*);
	return vfunc<vFuncFn>(this, 66)(this);
}

void g_surface::SetFontGlyphSet(unsigned long uFont, const char* chFontName, int iTall, int iWeight, int iBlur, int iScanLines, int iFlags, int nRangeMin, int nRangeMax)
{
	typedef void(__thiscall* vFuncFn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
	return vfunc<vFuncFn>(this, 67)(this, uFont, chFontName, iTall, iWeight, iBlur, iScanLines, iFlags, nRangeMin, nRangeMax);
}

void g_surface::GetTextSize(unsigned long uFont, const wchar_t* chText, int& iW, int& iH)
{
	typedef void(__thiscall* vFuncFn)(void*, unsigned long, const wchar_t*, int&, int&);
	return vfunc<vFuncFn>(this, 76)(this, uFont, chText, iW, iH);
}

void g_surface::SetCursorAlwaysVisible(bool bVisible)
{
	typedef void(__thiscall* vFuncFn)(void*, bool);
	return vfunc<vFuncFn>(this, 52)(this, bVisible);
}

// Surface2

void g_surface2::DrawTextA(unsigned long uFont, int iX, int iY, int iAlignType, const Color& rgColor, const char* chText, ...)
{
	int len = strlen(chText);
	wchar_t* wBuf = new wchar_t[len];
	for (int i = 0; i < len; i++)
	{
		wBuf[i] = static_cast<wchar_t>(chText[i]);
	}

	int iW, iH;
	g_Interfaces::surface->GetTextSize(uFont, wBuf, iW, iH);

	if (iAlignType == 1)
		iX -= iW;
	else if (iAlignType == 2)
		iX -= iW / 2;

	g_Interfaces::surface->DrawSetTextColor(rgColor.r, rgColor.g, rgColor.b, rgColor.a);
	g_Interfaces::surface->DrawSetTextFont(uFont);
	g_Interfaces::surface->DrawSetTextPos(iX, iY);
	g_Interfaces::surface->DrawPrintText(wBuf, len);

	delete[] wBuf;
}

void g_surface2::DrawGradient(int x, int y, int w, int h, const Color& color, int iTR)
{
	auto transition = 0;

	for (auto i = 0; i < h; i++)
	{
		transition += iTR;
		g_Interfaces::surface->DrawSetColor(static_cast<int>(color.r) - transition, static_cast<int>(color.g) - transition, static_cast<int>(color.b) - transition, static_cast<int>(color.a));
		g_Interfaces::surface->DrawFilledRect(x, y + i, w, 1);
	}

	g_Interfaces::surface->DrawSetColor(255, 255, 255, 255);
}

g_surface* g_Interfaces::surface = new g_surface;
g_surface2* g_Interfaces::surface2 = new g_surface2;