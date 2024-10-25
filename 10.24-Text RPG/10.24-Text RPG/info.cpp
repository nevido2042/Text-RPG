#include "pch.h"
#include "info.h"
#include "misc.h"
//#include "TextRPG.h"

//tagInfo::tagInfo()
//{
//}

CInfo::CInfo()
{
	//cout << m_szName << __FUNCTION__ << endl;
	//system("pause");
}

char* CInfo::Get_Name()
{
	return m_szName;
}

CStat* CInfo::Get_Stat()
{
	return &m_Stat;
}

CStat* CInfo::Get_CurStat()
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
	m_iDay = _iDay;
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
	for (int i = 0; i < Get_CurStat()->Get_HP(); ++i)
	{
		cout << "■";
	}

	int iEmptyCount = Get_Stat()->Get_HP() - Get_CurStat()->Get_HP();
	for (int i = 0; i <iEmptyCount ; ++i)
	{
		if (i >= Get_Stat()->Get_HP())
			break;

		cout << "□";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "마나: ";
	SetPrintColor(DARK_BLUE);
	for (int i = 0; i < Get_CurStat()->Get_MP(); ++i)
	{
		cout << "★";
	}
	for (int i = 0; i < Get_Stat()->Get_MP() - Get_CurStat()->Get_MP(); ++i)
	{
		if (i >= Get_Stat()->Get_MP())
			break;

		cout << "☆";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "공격력: ";
	SetPrintColor(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->Get_STR(); ++i)
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
	Get_CurStat()->Set_HP(Get_Stat()->Get_HP());
	Get_CurStat()->Set_MP(Get_Stat()->Get_MP());
	Get_CurStat()->Set_STR(Get_Stat()->Get_STR());
	Get_CurStat()->Set_DEX(Get_Stat()->Get_DEX());
	Get_CurStat()->Set_LUK(Get_Stat()->Get_LUK());
	Get_CurStat()->Set_INT(Get_Stat()->Get_INT());
}
