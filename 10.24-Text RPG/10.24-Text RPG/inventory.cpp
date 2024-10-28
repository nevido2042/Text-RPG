#include "pch.h"
#include "inventory.h"
#include "misc.h"

CInven::CInven()
{
	ZeroMemory(m_pItemArray, sizeof(m_pItemArray));
	m_iItemCount = 0;
}

void CInven::Initialize()
{
	for (int i = 0; i < m_iItemCount; ++i)
	{
		Get_ItemArray()[i].Initialize();
	}
}

void CInven::Update()
{
}

void CInven::Release()
{
}

CItem* CInven::Get_ItemArray()
{
	return m_pItemArray;
}

void CInven::AddItem(CItem _item)
{
	if (m_iItemCount == MAX_INVEN)
	{
		cout << "아이템을 더 가질 수 없습니다." << endl;
		system("pause");
		return;
	}

	m_pItemArray[m_iItemCount++] = _item;
}

int CInven::RemoveItem(int _iNum)
{
	if (_iNum >= m_iItemCount)
	{
		cout << "아이템 없음." << endl;
		system("pause");
		return _ERROR;
	}

	--m_iItemCount;
	for (int i = _iNum; i < m_iItemCount - _iNum; ++i)
	{
		swap(m_pItemArray[i], m_pItemArray[i + 1]);
	}

	return SUCCESS;
}

void CInven::PrintAll()
{
	cout << "[소지품]" << endl;
	LINE_LINE;
	for (int i = 0; i < m_iItemCount; ++i)
	{
		cout << "[" << i + 1 << "] " ;
		m_pItemArray[i].PrintItem();
	}
	LINE_LINE;

}

void CInven::ClearInven()
{
	m_iItemCount = 0;
}

void CInven::SetMerchantInven()//상인 안에서 구현해야겠다 나중에
{
	extern CItem redPotion;

	ClearInven();

	/*ITEM item;
	item.iValue = 50;
	strcpy_s(item.szName, "빨간 물약");*/
	AddItem(redPotion);
}