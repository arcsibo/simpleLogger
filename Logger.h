#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
//#include "fmt/include/fmt/format.h"
#include <chrono>
#include <ctime>
#include <sstream> 
#include <time.h>
#include <algorithm>
#include <mutex>


#include <cstddef>
#include <utility>
#include <string>

/// show function name filename and line:
/// OpenFile (..\App\Src\OpenFile.cpp:30)
//#define __INFO__ fmt::format("{} ({}:{})", std::string(__FUNCTION__), std::to_string(__FILE__), std::to_string(__LINE__))
//#define __STD_FUNC__ (std::string(__func__))
//#define __INFO__ (__FILE__ "::" __STD_FUNC__ "(..):" __LINE__)

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define __INFO__ (__FILE__ ":" STRINGIZE(__LINE__))
//#define __INFO__ (__FILE__ "::" __FUNCTION__ "(..):" STRINGIZE(__LINE__))


//#define __INFO__ fmt::format("{} ({}:{})", std::string(__FUNCTION__), std::string(__FILE__), std::to_string(__LINE__))

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

constexpr char mConstLogFile[] = "logging.txt";

class Logging
{
public:
	Logging(Logging&& move)               = delete;
    Logging& operator=(Logging&& move)    = delete;
    void swap(Logging& other)             = delete;
    Logging(Logging const&)               = delete;
    Logging& operator=(Logging const&)    = delete;
	Logging(std::string type, bool tostdout) : mType(type), mToStdout(tostdout){};
protected:
	Logging() = delete;
	virtual ~Logging(){};

	std::string mType;
	bool mToStdout;

public:
	void operator<<(const std::string& str) 
	{
		if(mToStdout)
			std::cout << mType << " " << str << "\n";

		
		std::lock_guard<std::mutex> guard(m);

		std::string name = mConstLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << mType << " " << time2String() << str << "\n";
		file.close();
	}

	void operator<<(const char& chr) 
	{
		if(mToStdout)
			std::cout << mType << " " << chr << "\n";

		std::lock_guard<std::mutex> guard(m);

		std::string name = mConstLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << mType << " " << time2String() << chr << "\n";
		file.close();
	}

private:	
	std::mutex m;

};

class InfoLogging : public Logging
{
public:
InfoLogging() : Logging("[INFO]", true){};
~InfoLogging(){};
};

class DebugLogging : public Logging
{
public:
DebugLogging() : Logging("[DEBUG]", false){};
~DebugLogging(){};
};

class ErrorLogging : public Logging
{
public:
ErrorLogging() : Logging("[ERROR]", true){};
~ErrorLogging(){};
};

static InfoLogging		INFOLOGGING;
static DebugLogging		DEBUGLOGGING;
static ErrorLogging		ERRORLOGGING;


#endif