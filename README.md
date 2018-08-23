# simpleLogger
I created a(nother) simple logging system. 

to build example:
```
$ g++ --std=c++11 example.cpp Logger.h
```


## loggers

DEBUGLOGGING will show only in the text file. [DEBUG] 
INFOLOGGING wil show message to the stdout and the file too. [INFO]
ERRORLOGGING will show message to the stdout and the file too. [ERROR]

## example code

example code:
```cpp
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
```

## run the example code

```
$ ./a.out
[INFO] Main started.
[INFO] foobar started.
[ERROR] Fatal error
[INFO] Main ended.
```

## Example

```
$ cat logging.txt
[DEBUG] 23-08-2018 14:48:59 | example.cpp:19
[INFO] 23-08-2018 14:48:59 | Main started.
[DEBUG] 23-08-2018 14:48:59 | example.cpp:6
[INFO] 23-08-2018 14:48:59 | foobar started.
[ERROR] 23-08-2018 14:48:59 | Fatal error
[INFO] 23-08-2018 14:48:59 | Main ended.
```

