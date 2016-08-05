#pragma once

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

class g_surface
{
public:
	void DrawSetColor(int, int, int, int);
	void DrawFilledRect(int, int, int, int);
	void DrawOutlinedRect(int x, int y, int w, int h);
	void DrawLine(int x, int y, int w, int h);
	void DrawSetTextFont(unsigned long);
	void DrawSetTextColor(int, int, int, int);
	void DrawSetTextPos(int x, int y);
	void DrawPrintText(const wchar_t*, int);
	unsigned long CreateFonts();
	void SetFontGlyphSet(unsigned long, const char*, int, int, int, int, int, int nRangeMin = 0, int nRangeMax = 0);
	void GetTextSize(unsigned long, const wchar_t*, int&, int&);
	void SetCursorAlwaysVisible(bool bVisible);
};

class g_surface2
{
public:
	static void DrawTextA(unsigned long, int, int, int, const Color&, const char*, ...);
	static void DrawGradient(int x, int y, int w, int h, const Color& color, int iTR = 1);
};