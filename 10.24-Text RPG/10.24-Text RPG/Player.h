#pragma once
#include "info.h"
#include "InputManager.h"

class CEnemy;
class CMerchant;

class CPlayer
{
	CInfo* m_pInfo;

public:
	CPlayer();
	~CPlayer();

public:
	CInfo& Get_Info();
	void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();

public:
	int Select_Task(CInputManager* _pInputManager, CMerchant* _pMerchant);
	void Select_Dungeon(CInputManager* _pInputManager);
	void Buy_Item(CMerchant* _pMerchant, CInputManager* _pInputManager);
	void Sell_Item(CMerchant* _pMerchant, CInputManager* _pInputManager);
	void Try_Attack(CEnemy* _pTarget);
	int Roll_Dice(int _iValue);
	int Select_Item(CInputManager* _InputManager, CInfo* _pTarget);

//public:
//	static int iTryCount;
};

//int g_iNum = 0;

//int CPlayer::iTryCount = 0;

