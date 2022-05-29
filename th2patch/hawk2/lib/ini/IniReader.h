#pragma once

class CIniReader
{
public:
	CIniReader(char* szFileName); 
	int ReadInt(char* szSection, char* szKey, int iDefaultValue);
	float ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
	bool ReadBool(char* szSection, char* szKey, bool bolDefaultValue);
	std::string ReadString(char* szSection, char* szKey, const char* szDefaultValue);

private:
	char m_szFileName[255];
};