#pragma once
#include "item.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget);

CItem redPotion("���� ����", 50, RecoveryHP);
//{
//	"���� ����",
//	50,
//	RecoveryHP
//};