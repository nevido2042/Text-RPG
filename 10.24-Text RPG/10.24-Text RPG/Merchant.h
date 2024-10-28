#pragma once
#include "info.h"
#include "Player.h"//나중에 빼야할 듯?
#include "InputManager.h"

class CMerchant
{
	CInfo* m_pInfo;

public:
	CMerchant();
	~CMerchant();

public:
	CInfo& Get_Info();
	void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();

public:
	void Set_Merchant_Inven();
	void Open_Shop(CPlayer* _pPlayer, CInputManager* _pInputManager);
	void Render_Shop(CPlayer* _pPlayer);

};

