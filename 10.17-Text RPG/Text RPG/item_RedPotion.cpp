#include "item_RedPotion.h"
#include "pch.h"

#include "info.h"

void RecoveryHP(INFO* _pUser, INFO* _pTarget)
{
	//ȸ����
	const int Amount(3);

	_pUser->curStat.iHP += Amount;
	if (_pUser->curStat.iHP > _pUser->stat.iHP)
	{
		//��ġ�� ����
		_pUser->curStat.iHP = _pUser->stat.iHP;
	}

	cout << _pUser->szName << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	system("pause");
}