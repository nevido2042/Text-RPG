#include "pch.h"
#include "info.h"
#include "misc.h"
//#include "TextRPG.h"

void tagInfo::PrintName()
{
	cout << "ÀÌ¸§: " << szName << endl;
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
