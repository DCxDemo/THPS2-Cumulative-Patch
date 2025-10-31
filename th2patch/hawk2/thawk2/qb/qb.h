#pragma once

using namespace std;

namespace QB
{
	struct VariableEntry {
		unsigned int Checksum;
		char Type;
		void* pValue = NULL;

		VariableEntry* Prev = NULL;
		VariableEntry* Next = NULL;
	};

	struct ScriptFileEntry {
		string* Name;
		void* pData = NULL;
		int Size = 0;

		ScriptFileEntry* Prev = NULL;
		ScriptFileEntry* Next = NULL;
	};

	struct ScriptEntry {
		void* pStart = NULL;
		void* pEnd = NULL;

		ScriptEntry* Prev = NULL;
		ScriptEntry* Next = NULL;
	};

	uint32_t crc32ns(const char* data);

	void LoadScript(string name);
	void ParseScript(void* p);
	int GetInt(unsigned int checksum);
	float GetFloat(unsigned int checksum);
	VariableEntry* FindVariable(unsigned int checksum);
}