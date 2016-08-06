#pragma once

class g_console
{
public:
	bool bOpen;
	static void Create(char*);
	static void Print(std::string sMessage, ...);
	static void centerPrint(const char* sMessage);
	static void ConsolePrint(const char* szMsg, bool bWarn, ...);
	static void Visible(bool);
};