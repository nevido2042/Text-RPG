#pragma once
#include "item.h"

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