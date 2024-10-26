#include "pch.h"
#include "inventory.h"
#include "misc.h"

CInven::CInven()
{
	//cout << __FUNCTION__ << endl;
	//system("pause");

}

void CInven::Initialize()
{
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
		cout << "�������� �� ���� �� �����ϴ�." << endl;
		system("pause");
		return;
	}

	m_pItemArray[m_iItemCount++] = _item;
}

int CInven::RemoveItem(int _iNum)
{
	if (_iNum >= m_iItemCount)
	{
		cout << "������ ����." << endl;
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
	cout << "[����ǰ]" << endl;
	for (int i = 0; i < m_iItemCount; ++i)
	{
		cout << i + 1 << '.';
		m_pItemArray[i].PrintItem();
	}
}

void CInven::ClearInven()
{
	m_iItemCount = 0;
}

void CInven::SetMerchantInven()
{
	extern CItem redPotion;

	ClearInven();

	/*ITEM item;
	item.iValue = 50;
	strcpy_s(item.szName, "���� ����");*/
	AddItem(redPotion);
}