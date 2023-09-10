#pragma once
#include "Mem.h"

extern int* TotalCClassUsage;
extern int* Used;

class CClass
{
public:
	void* operator new(size_t size);
	void operator delete(void* p);
};