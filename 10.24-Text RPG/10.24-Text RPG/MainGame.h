#pragma once
//#include "info.h"
#include "InputManager.h"
#include "Player.h"
#include "Merchant.h"

class CMainGame
{
	enum DUNGEON { Grassland = 1, Mountain, Cave };

	CInputManager* m_pInputManager;
	CPlayer* m_pPlayer;
	CMerchant* m_pMerchant;

public:
	CPlayer& Get_Player();
	void Set_Player(CPlayer* _pPlayer);

	CMerchant& Get_Merchant();
	void Set_Merchant(CMerchant* _pMerchant);

	CInputManager& Get_InputManager();
	void Set_InputManager(CInputManager* _pInputManager);
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

public:
	void Print_MainMenu();
	void Create_Player();
	void Load_Player();
	void Save_Player();

	//void Select_Task();//info //player
	void Input_Name();//info //player
	void Set_Random_STAT();//stat 
	//void Select_Dungeon();//info //player
	//void Open_Shop();//info //merchant?
	//void Buy_Item();//info //player
	//void Sell_Item();//info //player
	//void Render_Shop();//info //merchant?
};

