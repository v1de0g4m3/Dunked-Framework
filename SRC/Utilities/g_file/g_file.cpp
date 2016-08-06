#include "../../sdk.h"
#include "time.h"

bool g_file::FileCreate(std::string file, std::string content)
{
	if (FileExists(file))
		return false;

	std::ofstream filestream;
	filestream.open(file);
	filestream << content;
	filestream.close();

	return true;
}

bool g_file::FileExists(std::string file)
{
	std::ifstream filestream(file.c_str());

	if (filestream.good())
	{
		filestream.close();
		return true;
	}

	filestream.close();
	return false;
}

bool g_file::FileRead(std::string file, std::string & read) const
{
	std::ifstream filestream;
	filestream.open(file);

	std::string line;

	if (!filestream.is_open())
		return false;

	int linenum = 0;
	while (getline(filestream, line))
	{
		linenum++;

		read.append(line);
		if (linenum > 1)
			read.push_back('\n');
	}

	filestream.close();

	return true;
}

bool g_file::FileEdit(std::string file, std::string content)
{
	if (!FileDelete(file.c_str()))
		return false;

	return FileCreate(file, content);
}

bool g_file::FileAppend(std::string file, std::string content)
{
	std::ofstream filestream;

	filestream.open(file, std::ios::out | std::ios::app);
	filestream << content;
	filestream.close();

	return true;
}

bool g_file::FileAppend_2(std::string file, std::string content)
{
	std::ofstream filestream;

	if (!filestream.is_open())
		return 0;

	filestream.open(file);
	filestream << content;
	filestream.close();

	return true;
}

int g_file::FileDelete(std::string file)
{
	return remove(file.c_str());
}

int g_file::DirCreate(std::string dir)
{
	return CreateDirectoryA(dir.c_str(), nullptr);
}

int g_file::DirDelete(std::string dir)
{
	return RemoveDirectoryA(dir.c_str());
}

bool g_file::WriteToLog(std::string fmt, ...)
{
	time_t now = time(nullptr);
	struct tm tstruct;
	tstruct = *localtime(&now);

	std::stringstream date;
	date << tstruct.tm_mday;
	date << "_" << 1 + tstruct.tm_mon;
	date << "_" << 1900 + tstruct.tm_year;

	std::stringstream tolog_s;

	tolog_s << "[" << tstruct.tm_hour << ":";
	tolog_s << tstruct.tm_min << ":";
	tolog_s << tstruct.tm_sec << "] ";

	tolog_s << fmt;

	return FileAppend(std::string("C:\\Dunked\\Logs\\") + date.str() + ".txt", tolog_s.str());
}

g_file* g_utilList::file = new g_file;

