#include "pch.h"
#include "info.h"
#include "misc.h"
//#include "TextRPG.h"

//tagInfo::tagInfo()
//{
//}

CInfo::CInfo()
{
}

char* CInfo::Get_Name()
{
	return m_szName;
}

STAT* CInfo::Get_Stat()
{
	return &m_Stat;
}

STAT* CInfo::Get_CurStat()
{
	return &m_CurStat;
}

CInven* CInfo::Get_Inven()
{
	return &m_Inven;
}

int CInfo::Get_Gold()
{
	return m_iGold;
}

int CInfo::Get_Day()
{
	return m_iDay;
}

void CInfo::Set_Day(int _iDay)
{
	m_iDay += _iDay;
}

void CInfo::IncreaseDay()
{
	++m_iDay;
}

void CInfo::AddGold(int _iGold)
{
	m_iGold += _iGold;
}

void CInfo::RenderStat()
{
	cout << "체력: ";
	SetPrintColor(DARK_RED);
	for (int i = 0; i < Get_CurStat()->iHP; ++i)
	{
		cout << "■";
	}

	int iEmptyCount = Get_Stat()->iHP - Get_CurStat()->iHP;
	for (int i = 0; i <iEmptyCount ; ++i)
	{
		if (i >= Get_Stat()->iHP)
			break;

		cout << "□";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "마나: ";
	SetPrintColor(DARK_BLUE);
	for (int i = 0; i < Get_CurStat()->iMP; ++i)
	{
		cout << "★";
	}
	for (int i = 0; i < Get_Stat()->iMP - Get_CurStat()->iMP; ++i)
	{
		if (i >= Get_Stat()->iMP)
			break;

		cout << "☆";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "공격력: ";
	SetPrintColor(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->iSTR; ++i)
	{
		cout << "†";
	}
	SetPrintColor(GRAY);
	cout << endl;
}

void CInfo::PrintName()
{
	cout << "이름: " << m_szName << endl;
	cout << endl;
}

void CInfo::PrintInfo()
{
	PrintName();
	//cout << "--------------------" << endl;
	RenderStat();
	Get_CurStat()->PrintDetailStat();
	cout << endl;
}

void CInfo::ResetStat()
{
	Get_CurStat()->iHP = Get_Stat()->iHP;
	Get_CurStat()->iMP = Get_Stat()->iMP;
	Get_CurStat()->iSTR = Get_Stat()->iSTR;
	Get_CurStat()->iDEX = Get_Stat()->iDEX;
	Get_CurStat()->iLUK = Get_Stat()->iLUK;
	Get_CurStat()->iINT = Get_Stat()->iINT;
}
