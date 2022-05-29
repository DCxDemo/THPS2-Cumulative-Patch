#include "stdafx.h"
#include "IniWriter.h"
#include <iostream>
#include <Windows.h>

char szValue[255];

CIniWriter::CIniWriter(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

void CIniWriter::WriteInt(char* szSection, char* szKey, int iValue)
{
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void CIniWriter::WriteFloat(char* szSection, char* szKey, float fltValue)
{
	sprintf(szValue, "%f", fltValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void CIniWriter::WriteBool(char* szSection, char* szKey, bool bolValue)
{
	sprintf(szValue, "%s", bolValue ? "True" : "False");
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void CIniWriter::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}