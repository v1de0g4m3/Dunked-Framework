#pragma once

typedef void(__fastcall *PaintTraverseFn)(void*, void*, unsigned int, bool, bool);

namespace g_PaintTraverse
{
	extern void Paint();
	extern void __fastcall Main(void*, void*, unsigned int, bool, bool);
};