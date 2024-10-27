#pragma once
#include "info.h"
#include "InputManager.h"

class CMainGame
{
	enum DUNGEON { Grassland = 1, Mountain, Cave };

	//int m_iInput; //인풋 매니저 클래스르 들어야하나
	CInputManager* m_pInputManager;
	CInfo* m_pPlayer;
	CInfo* m_pMerchant;
	//CInfo* m_pEnemy; //던전 헤더에서

public:
	//int& Get_Input();
	//void Set_Input(int _iInput);

	CInfo& Get_Player();
	void Set_Player(CInfo* _pPlayer);

	CInfo& Get_Merchant();
	void Set_Merchant(CInfo* _pMerchant);

	//CInfo& Get_Enemy();
	//void Set_Enemy(CInfo* _pEnemy);

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
	//int Receive_Input();
	//int Check_Input();
	void Create_Player();
	void Select_Task();
	void Load_Player();
	void Input_Name();
	void Set_Random_STAT();
	void Select_Dungeon();
	void Open_Shop();
	void Buy_Item();
	void Sell_Item();
	void Render_Shop();
	void Save_Player();
	//void Enter_Dungeon(int _iValue);
	//void Trigger_Random_Event(int _iValue);
	//void Face_Enemy(int _iValue);
	//void Render_Battle_Info();
	//void Start_Battle();
	//int Roll_Dice(int _iValue);
	//int Select_Item();
	//void Trigger_Trap(int _iValue);
	//void Find_Magic_Box(int _iValue);
};

