#include "stdafx.h"

void __trace(const char* format, ...)
{
	char buffer[1000];

	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);

	OutputDebugString(buffer);
}