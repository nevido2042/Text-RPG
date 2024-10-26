#pragma once
#include "item.h"

class CInven
{
	CItem m_pItemArray[MAX_INVEN] = {};
	int m_iItemCount = 0;
public:
	CInven();
public:
	void Initialize();
	void Update();
	void Release();
public:
	CItem* Get_ItemArray();
public:
	void AddItem(CItem _item);
	int RemoveItem(int _iNum);
	void PrintAll();
	void ClearInven();
	void SetMerchantInven();
};