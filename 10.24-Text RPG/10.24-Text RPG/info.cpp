#include "pch.h"
#include "info.h"
#include "misc.h"

CInfo::CInfo()
	:m_iDay(1), m_iGold(0)
{
	ZeroMemory(m_szName, sizeof(m_szName));
	//m_iDay = 1;
	//m_iGold = 0;

	ZeroMemory(&m_Stat, sizeof(CStat));
	ZeroMemory(&m_CurStat, sizeof(CStat));
	ZeroMemory(&m_Inven, sizeof(CInven));
}

CInfo::~CInfo()
{
	Release();
}

void CInfo::Initialize()
{
	Get_Inven()->Initialize();
	Get_CurStat()->Initialize();
	Get_Stat()->Initialize();
}

void CInfo::Update()
{
}

void CInfo::Release()
{
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
	Set_Color(DARK_RED);
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
	Set_Color(GRAY);
	cout << endl;

	cout << "마나: ";
	Set_Color(DARK_BLUE);
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
	Set_Color(GRAY);
	cout << endl;

	cout << "공격력: ";
	Set_Color(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->Get_STR(); ++i)
	{
		cout << "†";
	}
	Set_Color(GRAY);
	cout << endl;
}

void CInfo::PrintName() const
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
