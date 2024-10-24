#pragma once
#include "misc.h"

typedef struct tagInfo INFO;

typedef struct tagItem
{
	tagItem();
	tagItem(const char* _szName, int _iValue = 0, void(*_pUse)(INFO*, INFO*) = nullptr);

	char szName[NAME_LEN] = "";
	int iValue = 0; // 가치(단위: 골드)
	void PrintItem();
	void(*pUse)(INFO* _pUser, INFO* _pTarget) = nullptr;
	void Use(INFO* _pUser, INFO* _pTarget);
}ITEM;