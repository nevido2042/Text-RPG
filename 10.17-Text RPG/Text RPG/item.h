#pragma once
#include "misc.h"

typedef struct tagInfo INFO; //���漱��

typedef struct tagItem
{
	char szName[NAME_LEN] = "";
	int iValue = 0; // ��ġ(����: ���)
	void PrintItem();
	void Use(INFO* _pUser, INFO* _pTarget);
}ITEM;