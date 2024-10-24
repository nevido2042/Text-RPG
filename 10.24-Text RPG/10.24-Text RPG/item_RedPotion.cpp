#include "item_RedPotion.h"
#include "pch.h"

#include "info.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget)
{
	//회복량
	const int Amount(3);

	_pUser->curStat.iHP += Amount;
	if (_pUser->curStat.iHP > _pUser->stat.iHP)
	{
		//과치유 방지
		_pUser->curStat.iHP = _pUser->stat.iHP;
	}
	SetPrintColor(YELLOW);
	cout << _pUser->szName << " 은(는) " << Amount << "만큼 회복 되었다." << endl;
	SetPrintColor(GRAY);

	system("pause");
}