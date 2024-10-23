#include "pch.h"
#include "info.h"
#include "misc.h"
#include "TextRPG.h"

void tagInventory::AddItem(ITEM _item)
{
	if (iItemCount == MAX_INVEN)
	{
		cout << "�������� �� ���� �� �����ϴ�." << endl;
		system("pause");
		return;
	}

	itemArray[iItemCount++] = _item;
}

int tagInventory::RemoveItem(int _iNum)
{
	if (_iNum >= iItemCount)
	{
		cout << "������ ����." << endl;
		system("pause");
		return _ERROR;
	}

	--iItemCount;
	for (int i = _iNum; i < iItemCount - _iNum; ++i)
	{
		swap(itemArray[i], itemArray[i + 1]);
	}

	return SUCCESS;
}

void tagInventory::PrintAll()
{
	cout << "[����ǰ]" << endl;
	for (int i = 0; i < iItemCount; ++i)
	{
		cout << i + 1 << '.';
		itemArray[i].PrintItem();
	}
}

void tagInventory::ClearInven()
{
	iItemCount = 0;
}

void tagInventory::SetMerchantInven()
{
	ClearInven();

	ITEM item;
	item.iValue = 50;
	strcpy_s(item.szName, "���� ����");
	AddItem(item);

}

void tagInfo::PrintName()
{
	cout << "�̸�: " << szName << endl;
	cout << endl;
}

void tagInfo::PrintInfo()
{
	PrintName();
	//cout << "--------------------" << endl;
	curStat.RenderStat();
	curStat.PrintDetailStat();
	cout << endl;
}

void tagInfo::ResetStat()
{
	curStat.iHP = stat.iHP;
	curStat.iMP = stat.iMP;
	curStat.iSTR = stat.iSTR;
	curStat.iDEX = stat.iDEX;
	curStat.iLUK = stat.iLUK;
	curStat.iINT = stat.iINT;
}
