# simpleLogger
I created a(nother) simple logging system. It could be standalone. It works on windows and linux too. (I haven't tried on Mac yet.)

## Example:

[DEBUG]	02-08-2018 11:20:59 | InitWSA(..\App\src\main.cpp:18) 			// (1)
[INFO]	02-08-2018 11:30:19 | Application started						// (2)
[DEBUG]	02-08-2018 11:20:59 | OpenFile (..\App\src\FileReader.cpp:32)	// (1)
[ERROR]	02-08-2018 13:11:03	| Error while OpenFile						// (3)


### (1)

void CClientManager::InitTCP()
{
	DEBUGLOGGING << __INIT__;

[DEBUG] 02-08-2018 11:20:59 | InitWSA(..\Application\src\main.cpp:18)