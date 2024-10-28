#pragma once
#include "info.h"
#include "InputManager.h"
#include "Merchant.h" //나중에 빼야할 듯

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
};

