#pragma once
#include "info.h"
#include "InputManager.h"
class CDungeon
{
	enum DUNGEON { Grassland = 1, Mountain, Cave };

	int m_iValue;
	CInfo* m_pPlayer;
	CInfo* m_pEnemy;
	CInputManager* m_pInputManager;

public:
	CDungeon();
	CDungeon(CInfo* _pPlayer, int _iValue, CInputManager* _InputManager);
	~CDungeon();
	
public:
	CInfo& Get_Player();

	int Get_Value();

	CInputManager& Get_InputManager();

	CInfo& Get_Enemy();
	void Set_Enemy(CInfo* _pEnemy);

public:
	void Initialize();
	void Update();
	void Release();
public:
	void Render_Battle_Info();
	void Start_Battle();
	void Trigger_Random_Event(int _iValue);
	void Face_Enemy(int _iValue);
	void Trigger_Trap(int _iValue);
	void Find_Magic_Box(int _iValue);
};

