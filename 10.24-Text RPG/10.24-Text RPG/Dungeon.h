#pragma once
#include "info.h"
#include "InputManager.h"
#include "Enemy.h"

class CPlayer;

class CDungeon
{
	int m_iValue;
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy;
	CInputManager* m_pInputManager;

public:
	enum DUNGEON { Grassland = 1, Mountain, Cave };
public:
	CDungeon();
	CDungeon(CPlayer* _pPlayer, int _iValue, CInputManager* _InputManager);
	~CDungeon();
	
public:
	CPlayer& Get_Player();

	int Get_Value();

	CInputManager& Get_InputManager();

	CEnemy& Get_Enemy();
	void Set_Enemy(CEnemy* _pEnemy);

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

