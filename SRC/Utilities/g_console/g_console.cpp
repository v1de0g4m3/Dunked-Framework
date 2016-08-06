#include "../../sdk.h"

void g_console::Create(char* chTitle)
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	AllocConsole();
	auto hwnd = GetConsoleWindow();
	auto hMenu = GetSystemMenu(hwnd, FALSE);
	if (!hwnd || !hMenu) return;
	DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

	FILE* fp;
	fp = freopen("CONIN$", "r", stdin);
	fp = freopen("CONOUT$", "w", stdout); //-V519
	// For anyone reading this, I use PVS static analyzer, the above supresses a warning

	SetConsoleTitleA(chTitle);

	g_utilList::console->bOpen = false;
}

void g_console::Print(std::string sMessage, ...)
{
	char buf[1024];
	va_list vlist;
	va_start(vlist, sMessage);
	_vsnprintf(buf, sizeof(buf), sMessage.c_str(), vlist);
	va_end(vlist);

	printf("%s", buf);

	g_utilList::file->WriteToLog(sMessage);
}

void g_console::centerPrint(std::string sMessage)
{
	int l = sMessage.length();
	auto pos = static_cast<int>((80 - l) / 2);
	for (auto i = 0; i < pos; i++)
		g_utilList::console->Print(" ");

	g_utilList::console->Print(sMessage);
}

typedef void(*msg)(char const* pMsg, ...);
typedef void(*warning)(char const* pMsg, ...);

void g_console::ConsolePrint(std::string sString, bool bWarn, ...)
{
	auto Msg = reinterpret_cast<msg>(GetProcAddress(g_Interfaces::grab->hTier0, "Msg"));
	auto Warning = reinterpret_cast<warning>(GetProcAddress(g_Interfaces::grab->hTier0, "Warning"));

	if (bWarn)
		Warning(sString.c_str());
	else
		Msg(sString.c_str());

	g_utilList::file->WriteToLog(sString);
}

void g_console::Visible(bool bVisible)
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	AllocConsole();
	ShowWindow(FindWindowA("ConsoleWindowClass", nullptr), bVisible);
	g_utilList::console->bOpen = bVisible;
};

g_console* g_utilList::console = new g_console;