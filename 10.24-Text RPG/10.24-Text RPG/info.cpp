#include "pch.h"
#include "info.h"
#include "misc.h"
//#include "TextRPG.h"

//tagInfo::tagInfo()
//{
//}

void tagInfo::RenderStat()
{
	cout << "체력: ";
	SetPrintColor(DARK_RED);
	for (int i = 0; i < curStat.iHP; ++i)
	{
		cout << "■";
	}

	int iEmptyCount = stat.iHP - curStat.iHP;
	for (int i = 0; i <iEmptyCount ; ++i)
	{
		if (i >= stat.iHP)
			break;

		cout << "□";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "마나: ";
	SetPrintColor(DARK_BLUE);
	for (int i = 0; i < curStat.iMP; ++i)
	{
		cout << "★";
	}
	for (int i = 0; i < stat.iMP - curStat.iMP; ++i)
	{
		if (i >= stat.iMP)
			break;

		cout << "☆";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "공격력: ";
	SetPrintColor(DAKR_YELLOW);
	for (int i = 0; i < curStat.iSTR; ++i)
	{
		cout << "†";
	}
	SetPrintColor(GRAY);
	cout << endl;
}

void tagInfo::PrintName()
{
	cout << "이름: " << szName << endl;
	cout << endl;
}

void tagInfo::PrintInfo()
{
	PrintName();
	//cout << "--------------------" << endl;
	RenderStat();
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
