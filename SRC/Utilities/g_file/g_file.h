#pragma once

class g_file
{
public:
	static bool FileCreate(const std::string& file, const std::string& content);
	static bool FileExists(const std::string& file);
	bool FileRead(const std::string& file, std::string& read) const;
	static bool FileEdit(const std::string& file, const std::string& content);
	static bool FileAppend(const std::string& file, const std::string& content);
	static bool FileAppend_2(const std::string& file, const std::string& content);
	static int FileDelete(const std::string& file);
	static int DirCreate(const std::string& dir);
	static int DirDelete(const std::string& dir);
	static bool WriteToLog(const std::string& fmt, ...);
};