#include "item_RedPotion.h"
#include "pch.h"

#include "info.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget)
{
	const int Amount(3);
	_pUser->curStat.iHP += Amount;
	cout << _pUser->szName << " 은(는) " << Amount << "만큼 회복 되었다." << endl;
	system("pause");
}
