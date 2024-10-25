#pragma once
#include "item.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget);

CItem redPotion("說除 僭擒", 50, RecoveryHP);
//{
//	"說除 ん暮",
//	50,
//	RecoveryHP
//};