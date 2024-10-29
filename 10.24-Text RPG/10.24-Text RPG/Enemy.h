#pragma once
#include "info.h"
#include "Player.h"
class CEnemy
{
	CInfo* m_pInfo;
public:
	CEnemy();
	~CEnemy();

public:
	CInfo& Get_Info();
	void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();

public:
	void Try_Attack(CPlayer* _pTarget);
	int Roll_Dice(int _iValue);

};

