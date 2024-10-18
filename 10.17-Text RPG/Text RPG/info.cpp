#include "pch.h"
#include "info.h"

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

void tagStat::SetStatRandom()
{
	const int iMaxPoint = iStatCount * 2;
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