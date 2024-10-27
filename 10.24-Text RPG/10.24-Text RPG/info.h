#pragma once
#include "misc.h"

//#include "item.h"
#include "stat.h"
#include "inventory.h"
#include "InputManager.h"


class CInfo
{
	char m_szName[NAME_LEN * 2];
	int m_iDay;
	int m_iGold;

	CStat m_Stat; //�����Ҵ��� �ϴ°� ������? �Ҵ�,��ȯ�� ���� �� �����ѵ�
	CStat m_CurStat;//�����Ҵ��� �ϴ°� ������? �Ҵ�,��ȯ�� ���� �� �����ѵ�
	CInven m_Inven;//�����Ҵ��� �ϴ°� ������? �Ҵ�,��ȯ�� ���� �� �����ѵ�

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
	int Select_Item(CInputManager* _InputManager, CInfo* _pTarget);
	//void Select_Task();
	//int Receive_Input();
	//int Check_Input();
};