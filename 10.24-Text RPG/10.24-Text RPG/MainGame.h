#pragma once
#include "info.h"

class CMainGame
{
	int m_iInput;
	CInfo* m_pPlayer;
public:
	int& Get_Input();
	void Set_Input(int _iInput);

	CInfo& Get_Player();
	void Set_Player(CInfo* _pPlayer);
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
};

