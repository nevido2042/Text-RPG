#include "item_RedPotion.h"
#include "pch.h"

#include "info.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget)
{
	const int Amount(3);
	_pUser->curStat.iHP += Amount;
	cout << _pUser->szName << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	system("pause");
}
