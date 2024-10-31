#pragma once
//#include "info.h"
#include "Player.h"
#include "Entity.h"

class CEnemy: public CEntity
{
	//CInfo* m_pInfo;
public:
	CEnemy();
	~CEnemy();

public:
	//CInfo& Get_Info();
	//void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();

public:
	void Try_Attack(CPlayer* _pTarget);
	int Roll_Dice(int _iValue);

};

