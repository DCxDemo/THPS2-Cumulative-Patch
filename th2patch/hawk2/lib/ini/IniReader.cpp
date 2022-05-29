#include "stdafx.h"
#include "IniReader.h"
#include <iostream>
#include <Windows.h>

CIniReader::CIniReader(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

int CIniReader::ReadInt(char* szSection, char* szKey, int iDefaultValue)
{
	int iResult = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, m_szFileName);

	return iResult;
}

float CIniReader::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	float fltResult;

	sprintf(szDefault, "%f",fltDefaultValue);
	GetPrivateProfileString(szSection,  szKey, szDefault, szResult, 255, m_szFileName);
	fltResult = atof(szResult);

	return fltResult;
}

bool CIniReader::ReadBool(char* szSection, char* szKey, bool bolDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	bool bolResult;

	sprintf(szDefault, "%s", bolDefaultValue? "1" : "0");
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName); 
	bolResult = (strcmp(szResult, "1") == 0) ? true : false;

	return bolResult;
}

std::string CIniReader::ReadString(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection,  szKey, szDefaultValue, szResult, 255, m_szFileName); 

	printf("INI string: %s\r\n", szResult);

	return std::string(szResult);
}