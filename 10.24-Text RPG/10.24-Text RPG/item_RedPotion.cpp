#include "pch.h"
#include "item_RedPotion.h"

#include "info.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget)
{
	//ȸ����
	const int Amount(3);

	_pUser->Get_CurStat()->iHP += Amount;
	if (_pUser->Get_CurStat()->iHP > _pUser->Get_Stat()->iHP)
	{
		//��ġ�� ����
		_pUser->Get_CurStat()->iHP = _pUser->Get_Stat()->iHP;
	}
	SetPrintColor(YELLOW);
	cout << _pUser->Get_Name() << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	SetPrintColor(GRAY);

	system("pause");
}