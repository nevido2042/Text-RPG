#pragma once
#include "item.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget);

ITEM redPotion("���� ����", 50, RecoveryHP);
//{
//	"���� ����",
//	50,
//	RecoveryHP
//};