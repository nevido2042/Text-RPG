#pragma once
#include "item.h"

class CInven
{
	ITEM m_pItemArray[MAX_INVEN] = {};
	int m_iItemCount = 0;

public:
	ITEM* Get_ItemArray();
public:
	void AddItem(ITEM _item);
	int RemoveItem(int _iNum);
	void PrintAll();
	void ClearInven();
	void SetMerchantInven();
};