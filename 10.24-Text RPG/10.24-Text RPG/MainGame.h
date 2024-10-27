#pragma once
#include "info.h"
#include "InputManager.h"

class CMainGame
{
	enum DUNGEON { Grassland = 1, Mountain, Cave };

	CInputManager* m_pInputManager;
	CInfo* m_pPlayer;
	CInfo* m_pMerchant;

public:
	CInfo& Get_Player();
	void Set_Player(CInfo* _pPlayer);

	CInfo& Get_Merchant();
	void Set_Merchant(CInfo* _pMerchant);

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
	void Select_Task();//info
	void Load_Player();
	void Input_Name();//info
	void Set_Random_STAT();//stat
	void Select_Dungeon();
	void Open_Shop();
	void Buy_Item();
	void Sell_Item();
	void Render_Shop();
	void Save_Player();
};

