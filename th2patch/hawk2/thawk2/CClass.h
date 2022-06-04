#pragma once
#include "thawk2/Mem.h"

extern int* TotalCClassUsage;
extern int* Used;

class CClass
{
public:
	void* operator new(size_t size);
	void operator delete(void* p);
};