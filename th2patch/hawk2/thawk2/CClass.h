#pragma once

extern int* TotalCClassUsage;
extern int* Used;
extern void* testMenu;

class CClass
{
public:
	void* operator new(size_t size);
	void operator delete(void* p);
};

typedef void* (*_new_CClass_t)(int size);
static const _new_CClass_t	_new_CClass = (_new_CClass_t)0x00466b00;



//void CreateTestMenu();