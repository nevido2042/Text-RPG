#pragma once
#include "item.h"

class CInven
{
	CItem m_pItemArray[MAX_INVEN];//동적할당을 하는게 좋은가? 할당,반환이 자주 일어날 듯
	int m_iItemCount;
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