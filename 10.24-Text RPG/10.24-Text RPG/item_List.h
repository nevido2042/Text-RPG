#pragma once
//#include "item.h"
#include "Entity.h"
#include "Consumable_Item.h"
#include "Equipment_Item.h"

//void RecoveryHP(CInfo* _pUser, CInfo* _pTarget);
void STR_Up(CEntity* _pUser);

//CItem redPotion("���� ����", 50, RecoveryHP);
//{
//	"���� ����",
//	50,
//	RecoveryHP
//};

//CItem swordOfLegend("������ ��", 999, nullptr, STR_Up);

class CRedPotion : public CConsumable_Item
{
public:
	CRedPotion();
public:
	virtual int Use(CEntity* _pUser, CEntity* _pTarget) override;
};

class CSmall_RedPotion : public CConsumable_Item
{
public:
	CSmall_RedPotion();
public:
	virtual int Use(CEntity* _pUser, CEntity* _pTarget) override;
};

class CSword_Of_Legend : public CEquipment_Item
{
public:
	CSword_Of_Legend();
public:
	virtual int Equip(CEntity* _pUser) override;
	virtual int Unequip(CEntity* _pUser) override;
};

