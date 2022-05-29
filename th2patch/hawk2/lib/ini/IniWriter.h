#pragma once

class CIniWriter
{
public:
	CIniWriter(char* szFileName); 
	void WriteInt(char* szSection, char* szKey, int iValue);
	void WriteFloat(char* szSection, char* szKey, float fltValue);
	void WriteBool(char* szSection, char* szKey, bool bolValue);
	void WriteString(char* szSection, char* szKey, char* szValue);

private:
	char m_szFileName[255];
};