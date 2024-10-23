#pragma once
#include "misc.h"

typedef struct tagInfo INFO; //전방선언

typedef struct tagItem
{
	char szName[NAME_LEN] = "";
	int iValue = 0; // 가치(단위: 골드)
	void PrintItem();
	void Use(INFO* _pUser, INFO* _pTarget);
}ITEM;