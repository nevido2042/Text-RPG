#pragma once
#include "item.h"

class CInven
{
	CItem m_pItemArray[MAX_INVEN];//�����Ҵ��� �ϴ°� ������? �Ҵ�,��ȯ�� ���� �Ͼ ��
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