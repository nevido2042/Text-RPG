#pragma once
#include "misc.h"

//#include "item.h"
#include "stat.h"
#include "inventory.h"


typedef struct tagInfo
{
	tagInfo();

	char szName[NAME_LEN * 2] = "";
	int iDay = 1;
	STAT stat;
	STAT curStat;
	INVEN inven;
	int iGold = 0;
	
	void RenderStat();
	void PrintName();
	void PrintInfo();
	void ResetStat();
}INFO;