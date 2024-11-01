#pragma once
//#include "info.h"
#include "Entity.h"
#include "InputManager.h"

class CPlayer;

class CMerchant: public CEntity
{
	//CInfo* m_pInfo;

public:
	CMerchant();
	~CMerchant();

public:
	//CInfo& Get_Info();
	//void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();

public:
	void Set_Merchant_Inven();
	void Set_Dungeon_Merchant_Inven();
	void Open_Shop(CPlayer* _pPlayer, CInputManager* _pInputManager);
	void Render_Shop(CPlayer* _pPlayer);

};

