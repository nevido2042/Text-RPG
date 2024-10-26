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
	~CInfo();
public:
	void Initialize();
	void Update();
	void Release();
public:
	char* Get_Name();
	
	CStat* Get_Stat();
	
	CStat* Get_CurStat();
	
	CInven* Get_Inven();

	int Get_Gold();

	int Get_Day();
	void Set_Day(int _iDay);
public:
	void IncreaseDay();
	void AddGold(int _iGold);
	void RenderStat();
	void PrintName();
	void PrintInfo();
	void ResetStat();
	void Try_Attack(CInfo* _pTarget);
	int Roll_Dice(int _iValue);
	//void Select_Task();
	//int Receive_Input();
	//int Check_Input();
};