
#ifndef __STDAFX_H
#define __STDAFX_H


	#define WIN32_LEAN_AND_MEAN		
	#define DEBUG_FUNCTIONS

	#include <windows.h>
	#include <string>

#define NS_NULL 0xFFFFFFFF

#define MAX_BUFFER_SIZE 256

#define TRG_FILE_VERSION 2
#define TRG_PROJ_VERSION 0

#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 240

	void __trace(const char* format, ...);

	#ifdef DEBUG_FUNCTIONS
		#define _trace(...) __trace(__VA_ARGS__);
	#else
		#define _trace(...)
	#endif

#endif // __STDAFX_H