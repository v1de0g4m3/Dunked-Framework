#pragma once

class g_file
{
public:
	static bool FileCreate(std::string file, std::string content);
	static bool FileExists(std::string file);
	bool FileRead(std::string file, std::string &read) const;
	static bool FileEdit(std::string file, std::string content);
	static bool FileAppend(std::string file, std::string content);
	static bool FileAppend_2(std::string file, std::string content);
	static int FileDelete(std::string file);
	static int DirCreate(std::string dir);
	static int DirDelete(std::string dir);
	static bool WriteToLog(std::string fmt, ...);
};