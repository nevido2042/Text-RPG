#pragma once
#include "info.h"

class CMainGame
{
	enum DUNGEON { Grassland = 1, Mountain, Cave };

	int m_iInput;
	CInfo* m_pPlayer;
	CInfo* m_pMerchant;
	CInfo* m_Enemy;

public:
	int& Get_Input();
	void Set_Input(int _iInput);

	CInfo& Get_Player();
	void Set_Player(CInfo* _pPlayer);

	CInfo& Get_Merchant();
	void Set_Merchant(CInfo* _pMerchant);

	CInfo& Get_Enemy();
	void Set_Enemy(CInfo* _pEnemy);
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

public:
	void Print_MainMenu();
	int Receive_Input();
	int Check_Input();
	void Create_Player();
	void Select_Task();
	void Load_Player();
	void Input_Name();
	void Select_Dungeon();
	void Open_Shop();
	void Buy_Item();
	void Sell_Item();
	void Render_Shop();
	void Save_Player();
	void Enter_Dungeon(int _iValue);
	void Trigger_Random_Event(int _iValue);
	void Face_Enemy(int _iValue);
	void Render_Battle_Info();//적도 멤버로 만들어야 겠다.
	void Start_Battle();//적도 멤버로 만들어야 겠다.
	void Try_Attack(CInfo* _pAttacker, CInfo* _pTarget);
	int Roll_Dice(int _iValue);
	int Select_Item();//적도 멤버로 만들어야 겠다.
	void Trigger_Trap(int _iValue);
	void Find_Magic_Box(int _iValue);
};

