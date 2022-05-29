#pragma once

#include <windows.h>
#include <stdint.h>

class CPatch
{
private:
	inline static void Patch(void* address, void* data, int size)
	{
		unsigned long protect[2];
		VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &protect[0]);
		memcpy(address, data, size);
		VirtualProtect(address, size, protect[0], &protect[1]);
	}
public:
	inline static void Nop(int address, int size)
	{
		unsigned long protect[2];
		VirtualProtect((void *)address, size, PAGE_EXECUTE_READWRITE, &protect[0]);
		memset((void *)address, 0x90, size);
		VirtualProtect((void *)address, size, protect[0], &protect[1]);
	}
	inline static void RedirectCall(int address, void *func)
	{
		int temp = 0xE8;
		Patch((void *)address, &temp, 1);
		temp = (int)func - ((int)address + 5);
		Patch((void *)((int)address + 1), &temp, 4);
	}
	inline static void RedirectJump(int address, void *func)
	{
		int temp = 0xE9;
		Patch((void *)address, &temp, 1);
		temp = (int)func - ((int)address + 5);
		Patch((void *)((int)address + 1), &temp, 4);
	}
	inline static void SetChar(int address, char value)
	{
		Patch((void *)address, &value, 1);
	}
	inline static void SetShort(int address, short value)
	{
		Patch((void *)address, &value, 2);
	}
	inline static void SetInt(int address, int value)
	{
		Patch((void *)address, &value, 4);
	}
	inline static void SetFloat(int address, float value)
	{
		Patch((void *)address, &value, 4);
	}
	inline static void SetDouble(int address,double value)
	{
		Patch((void *)address, &value, 8);
	}
	inline static void SetPointer(int address, void *value)
	{
		Patch((void *)address, &value, 4);
	}
	inline static int SetBytes(int address, uint8_t *data, size_t size)
	{
		Patch((void *)address, &data, size);
	}
};