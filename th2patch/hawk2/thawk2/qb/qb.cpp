#include "stdafx.h"

#include "qb.h"

using namespace std;

#define OPCODE_TERMINATOR 0x00
#define OPCODE_NEWLINE 0x01
#define OPCODE_NEWLINE_DEBUG 0x02
#define OPCODE_ASSIGN 0x07
#define OPCODE_VAR 0x16
#define OPCODE_INTEGER 0x17
#define OPCODE_FLOAT 0x1A
#define OPCODE_SYMBOL 0x2B

// a very limited basic QB implementation, the idea was to maybe store data like vars, gaps and goals, etc
// can be safely removed as not used currently for anything
namespace QB
{
	// https://github.com/Michaelangel007/crc32
	uint32_t crc32ns(const char* data)
	{
		uint32_t crc = -1;

		char* pChar = (char*)data;

		while (*pChar != 0)
		{
			char c = *pChar;

			// lowercase
			if (c >= 'A' && c <= 'Z') c += 32;

			// only backslashes
			if (c == '/') c = '\\';

			crc = crc ^ c;

			for (int bit = 0; bit < 8; bit++)
			{
				if (crc & 1)
					crc = (crc >> 1) ^ 0xEDB88320;
				else          
					crc = (crc >> 1);
			}

			pChar++;
		}

		// original returns ~crc here.
		return crc;
	}

	VariableEntry* Vars;
	ScriptEntry* Scripts;

	ScriptFileEntry* ScriptFiles;

	int numScriptsLoaded = 0;
	int numVariablesLoaded = 0;

	void LoadScript(string name)
	{
		int i = numScriptsLoaded;

		FILE* file = fopen(&name[0], "rb");

		if (file == NULL) {
			printf_s("Failed to load script.\n");
			return;
		}

		
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		void* p = malloc(size);

		if (p == NULL) {
			fclose(file);
			printf_s("Failed to allocate space.\n");
			return;
		}

		
		fseek(file, 0, SEEK_SET);
		fread(p, 1, size, file);

		ScriptFileEntry* entry = (ScriptFileEntry*)malloc(sizeof(ScriptFileEntry));

		entry->Name = new string(name);
		entry->Size = size;
		entry->pData = p;

		if (ScriptFiles != NULL) {
			entry->Prev = ScriptFiles;
			ScriptFiles->Next = entry;
		}

		ScriptFiles = entry;

		ParseScript(entry->pData);

		numScriptsLoaded++;
		
	}

	VariableEntry* FindVariable(unsigned int checksum)
	{
		VariableEntry* p = Vars;

		do
		{
			if (p == NULL) return NULL;

			if (p->Checksum == checksum) return p;

			p = p->Prev;

		} while (true);
	}

	int GetInt(unsigned int checksum)
	{
		VariableEntry* p = FindVariable(checksum);

		if (p == NULL || p->Type != OPCODE_INTEGER)
		{
			printf_s("variable not found!\n");
			return 0;
		}

		return *(int*)p->pValue;
	}

	float GetFloat(unsigned int checksum)
	{
		VariableEntry* p = FindVariable(checksum);

		if (p == NULL)
		{
			printf_s("variable not found!\n");
			return 0.0;
		}

		if (p->Type == OPCODE_FLOAT)
		{
			return *(float*)p->pValue;
		}

		if (p->Type == OPCODE_INTEGER)
		{
			return (float)*(int*)p->pValue;
		}

		printf_s("Shouldn't reach this!\n");
		return 0.0;
	}

	void AddVariable(unsigned int checksum)
	{
		printf_s("AddVariable %08X\n", checksum);

		VariableEntry* var = FindVariable(checksum);

		if (var != NULL)
		{
			printf_s("Already added.\n");
			return;
		}

		var = (VariableEntry*)malloc(sizeof(VariableEntry));

		if (var == NULL) {
			printf_s("Failed to allocate.\n");
			return;
		}

		var->Checksum = checksum;

		// doh
		var->Prev = NULL;
		var->Next = NULL;

		if (Vars != NULL)
		{
			Vars->Next = var;
			var->Prev = Vars;
		}
		
		Vars = var;

		numVariablesLoaded++;

		printf_s("Added variable: %08X\n", checksum);
	}

	char pendingAction = 0;

	char* ParseOpcode(char* p)
	{
		char op = *p;
		p++;

		switch (op)
		{
			case OPCODE_TERMINATOR:
				printf_s("script ended!\n");
				break;

			case OPCODE_NEWLINE:
				printf_s("newline!\n");
				break;

			case OPCODE_NEWLINE_DEBUG:
				printf_s("newline debug!\n");
				p += 4;
				break;

			case OPCODE_VAR:
				AddVariable(*(unsigned int*)p);
				p += 4;
				break;

			case OPCODE_ASSIGN:
				pendingAction = OPCODE_ASSIGN;
				printf_s(" < assign value > \n");
				break;

			case OPCODE_INTEGER:
				if (pendingAction == OPCODE_ASSIGN) {
					Vars->Type = OPCODE_INTEGER;
					Vars->pValue = (void*)p;
					pendingAction = 0;
				}
				p += 4;

				printf_s("int value %i\n", *(int*)Vars->pValue);
				break;

			case OPCODE_FLOAT:
				if (pendingAction == OPCODE_ASSIGN) {
					Vars->Type = OPCODE_FLOAT;
					Vars->pValue = (void*)p;
					pendingAction = 0;
				}
				p += 4;
				printf_s("float value %f\n", *(float*)Vars->pValue);
				break;

			case OPCODE_SYMBOL:
				printf_s("skipping symbol\n");
				p += 4;
				// find null termination
				while (*p != 0) p++;
				// and skip one more
				p++;
				break;

			default:
				printf_s("Unknown opcode!\n");
				return OPCODE_TERMINATOR;
		}

		return p;
	}

	void ParseScript(void* pScript)
	{
		char* p = (char*)pScript;

		while (*p != OPCODE_TERMINATOR)
		{
			p = ParseOpcode(p);
		}
	}
}