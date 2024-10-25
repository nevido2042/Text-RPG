#pragma once
#include "misc.h"

typedef struct tagInfo INFO;

class CItem
{
	char m_szName[NAME_LEN] = "";
	int m_iValue = 0; // 가치(단위: 골드)
	void(*m_pUse)(INFO* _pUser, INFO* _pTarget) = nullptr;
public:
	CItem();
	CItem(const char* _szName, int _iValue = 0, void(*_pUse)(INFO*, INFO*) = nullptr);
public:
	char* Get_Name();
	int Get_Value();
public:
	void Set_Value(int _iValue);
public:
	void Use(INFO* _pUser, INFO* _pTarget);
	void PrintItem();
};