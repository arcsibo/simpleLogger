#include "Logger.h"
#include <iostream> 

int foobar()
{
	DEBUGLOGGING << __INFO__;
	INFOLOGGING << "foobar started.";
	int foo = 1 + 1;

	if(foo < 3)
	{
		//ERRORLOGGING << fmt::format("{} {}", __INFO__, "something went wrong");
		ERRORLOGGING << "Fatal error";
	}
}

int main()
{
	DEBUGLOGGING << __INFO__;

	INFOLOGGING << "Main started.";
	foobar();
	INFOLOGGING << "Main ended.";

	return 0;
}
