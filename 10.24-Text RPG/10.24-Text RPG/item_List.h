#pragma once
#include "item.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget);

CItem redPotion("빨간 물약", 50, RecoveryHP);
//{
//	"빨간 포션",
//	50,
//	RecoveryHP
//};

CItem swordOfLegend("전설의 검", 999, nullptr);
