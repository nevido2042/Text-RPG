#pragma once
#include "item.h"
#include "stat.h"
//#include "inventory.h"

#include "misc.h"

//struct ITEM;

typedef struct tagInventory
{
	ITEM itemArray[MAX_INVEN] = {};
	int iItemCount = 0;
	void AddItem(ITEM _item);
	int RemoveItem(int _iNum);
	void PrintAll();
	void ClearInven();
	void SetMerchantInven();
}INVEN;

typedef struct tagInfo
{
	char szName[NAME_LEN * 2] = "";
	int iDay = 1;
	STAT stat;
	STAT curStat;
	INVEN inven;
	int iGold = 0;
	
	void PrintName();
	void PrintInfo();
	void ResetStat();
}INFO;