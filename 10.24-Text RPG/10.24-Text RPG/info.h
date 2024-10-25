#pragma once
#include "misc.h"

//#include "item.h"
#include "stat.h"
#include "inventory.h"


class CInfo
{
	char m_szName[NAME_LEN * 2] = "";
	int m_iDay = 1;
	CStat m_Stat;
	CStat m_CurStat;
	CInven m_Inven;
	int m_iGold = 0;
public:
	CInfo();
public:
	char* Get_Name();
	CStat* Get_Stat();
	CStat* Get_CurStat();
	CInven* Get_Inven();
	int Get_Gold();
	int Get_Day();
public:
	void Set_Day(int _iDay);
public:
	void IncreaseDay();
	void AddGold(int _iGold);
	void RenderStat();
	void PrintName();
	void PrintInfo();
	void ResetStat();
};