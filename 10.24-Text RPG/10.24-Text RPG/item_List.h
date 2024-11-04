#pragma once
#include "item.h"
#include "Entity.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget);
void STR_Up(CEntity* _pUser);

//CItem redPotion("���� ����", 50, RecoveryHP);
//{
//	"���� ����",
//	50,
//	RecoveryHP
//};

//CItem swordOfLegend("������ ��", 999, nullptr, STR_Up);

class CRedPotion : public CItem
{
public:
	CRedPotion(const char* _szName, int _iValue);
public:
	virtual void Use(CInfo* _pUser, CInfo* _pTarget) override;
};

class CSmall_RedPotion : public CItem
{
public:
	CSmall_RedPotion(const char* _szName, int _iValue);
public:
	virtual void Use(CInfo* _pUser, CInfo* _pTarget) override;
};

class CSword_Of_Legend : public CItem
{
public:
	CSword_Of_Legend(const char* _szName, int _iValue);
public:
	virtual void Use(CInfo* _pUser, CInfo* _pTarget) override;
};

