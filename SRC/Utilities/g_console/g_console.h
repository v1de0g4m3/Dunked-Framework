#pragma once

class g_console
{
public:
	bool bOpen;
	static void Create(char*);
	static void Print(std::string sMessage, ...);
	static void centerPrint(const std::string& sMessage);
	static void ConsolePrint(const std::string&, bool bWarn, ...);
	static void Visible(bool);
};