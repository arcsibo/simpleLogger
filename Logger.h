#pragma once

#include <iostream>
#include <fstream>
#include "format.h"
#include <chrono>
#include <ctime>
#include <sstream> 
#include <time.h>
#include <algorithm>
#include <mutex>

/// show function name filename and line:
/// OpenFile (..\App\Src\OpenFile.cpp:30)
#define __INFO__ fmt::format("{} ({}:{})", std::string(__FUNCTION__), std::to_string(__FILE__), std::to_string(__LINE__))

constexpr char constLogFile[] = "logging.txt";

/// actual time
static std::string time2String()
{
	
	std::time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S | ", timeinfo);
	std::string str(buffer);

	return str;
}

class InfoLogging
{
public:
	void operator<<(const std::string& str) 
	{
		std::string type = "[INFO]";
		std::cout << fmt::format("{} {}\n", type, str);

		std::lock_guard<std::mutex> guard(m);

		std::string name = constLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << type << " " << time2String() << str << "\n";
		file.close();
	}

private:
	std::mutex m;
};

class DebugLogging
{
public:
	void operator<<(const std::string& str) 
	{
		std::string type = "[DEBUG]";

		std::lock_guard<std::mutex> guard(m);

		std::string name = constLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << type << " " << time2String() << str << "\n";
		file.close();
	}

private:
	std::mutex m;
};

class ErrorLogging
{
public:
	void operator<<(const std::string& str) 
	{
		std::string type = "[ERROR]";
		std::cout << fmt::format("{} {}\n", type, str);

		std::lock_guard<std::mutex> guard(m);

		std::string name = constLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << type << " " << time2String() << str << "\n";
		file.close();
	}

private:
	std::mutex m;
};

static InfoLogging		INFOLOGGING;
static DebugLogging		DEBUGLOGGING;
static ErrorLogging		ERRORLOGGING;