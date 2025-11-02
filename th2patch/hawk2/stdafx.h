
#ifndef __STDAFX_H
#define __STDAFX_H


	#define WIN32_LEAN_AND_MEAN		
	#define DEBUG_FUNCTIONS

	#include <windows.h>
	#include <string>

	#define MAX_BUFFER_SIZE 256

	void __trace(const char* format, ...);

	#ifdef DEBUG_FUNCTIONS
		#define _trace(...) __trace(__VA_ARGS__);
	#else
		#define _trace(...)
	#endif

#endif // __STDAFX_H