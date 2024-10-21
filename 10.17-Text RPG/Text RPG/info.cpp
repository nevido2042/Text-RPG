#include "pch.h"
#include "info.h"
#include "misc.h"

void tagStat::RenderStat()
{
	//cout << "====================" << endl;
	cout << "체력: ";
	for (int i = 0; i < iHP; ++i)
	{
		cout << "■";
	}
	cout << endl;

	cout << "마나: ";
	for (int i = 0; i < iMP; ++i)
	{
		cout << "★";
	}
	cout << endl;

	cout << "공격력: ";
	for (int i = 0; i < iSTR; ++i)
	{
		cout << "†";
	}
	cout << endl;

	//cout << "====================" << endl;
}

void tagStat::PrintALL()
{
	//cout << "====================" << endl;
	cout << "HP: " << iHP << endl;
	cout << "MP: " << iMP << endl;
	cout << "STR: " << iSTR << endl;
	cout << "DEX: " << iDEX << endl;
	cout << "LUK: " << iLUK << endl;
	cout << "INT: " << iINT << endl;
	//cout << "====================" << endl;
	//system("pause");
}

void tagStat::PrintDetailStat()
{
	cout << "STR: " << iSTR << endl;
	cout << "DEX: " << iDEX << endl;
	cout << "LUK: " << iLUK << endl;
	cout << "INT: " << iINT << endl;
}

void tagStat::SetStatRandom(int _iValue)
{
	const int iMaxPoint = iStatCount * _iValue;
	int iRemainPoint = iTotalStat;

	SetRandomPoint(&iHP, &iRemainPoint, &iMaxPoint);
	SetRandomPoint(&iMP, &iRemainPoint, &iMaxPoint);
	SetRandomPoint(&iSTR, &iRemainPoint, &iMaxPoint);
	SetRandomPoint(&iDEX, &iRemainPoint, &iMaxPoint);
	SetRandomPoint(&iLUK, &iRemainPoint, &iMaxPoint);
	//iINT = iRemainPoint;
	SetRandomPoint(&iINT, &iRemainPoint, &iMaxPoint);
}

void tagStat::SetRandomPoint(int* _iStatPoint, int* _iRemainPoint, const int* _iMaxPoint)
{
	int iRandomPoint = rand() % *_iMaxPoint + 1;
	if (*_iRemainPoint - iRandomPoint <= 0)
	{
		*_iStatPoint = *_iRemainPoint;
		*_iRemainPoint = 0;
		return;
	}

	*_iStatPoint = iRandomPoint;
	*_iRemainPoint -= iRandomPoint;
}

void tagINFO::PrintName()
{
	cout << "이름: " << szName << endl;
	cout << endl;
}

void tagINFO::PrintInfo()
{
	PrintName();
	//cout << "--------------------" << endl;
	curStat.RenderStat();
	curStat.PrintDetailStat();
	cout << endl;
}

void tagINFO::ResetStat()
{
	curStat.iHP = stat.iHP;
	curStat.iMP = stat.iMP;
	curStat.iSTR = stat.iSTR;
	curStat.iDEX = stat.iDEX;
	curStat.iLUK = stat.iLUK;
	curStat.iINT = stat.iINT;
}

void tagInventory::AddItem(ITEM _item)
{
	inven[iItemCount++] = _item;
}

int tagInventory::RemoveItem(int _iNum)
{
	if (_iNum >= iItemCount)
	{
		cout << "아이템 없음." << endl;
		system("pause");
		return _ERROR;
	}

	--iItemCount;
	for (int i = _iNum; i < iItemCount - _iNum; ++i)
	{
		swap(inven[i], inven[i + 1]);
	}

	return SUCCESS;
}

void tagInventory::PrintAll()
{
	cout << "[소지품]" << endl;
	for (int i = 0; i < iItemCount; ++i)
	{
		cout << i + 1 << '.';
		inven[i].PrintItem();
	}
}

void tagItem::PrintItem()
{
	//cout << iValue << endl;
	cout << szName;
	SetPrintColor(YELLOW);
	cout<<" (" << iValue << "G)" << endl;
	SetPrintColor(GRAY);

}
