#pragma once
#include "item.h"
#include "Entity.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget);
void STR_Up(CEntity* _pUser);

CItem redPotion("���� ����", 50, RecoveryHP);
//{
//	"���� ����",
//	50,
//	RecoveryHP
//};

CItem swordOfLegend("������ ��", 999, nullptr, STR_Up);
