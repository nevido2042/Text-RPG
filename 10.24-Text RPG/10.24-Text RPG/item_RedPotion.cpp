#include "pch.h"
#include "item_List.h"

#include "info.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget)
{
	//ȸ����
	const int Amount(3);

	_pUser->Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_CurStat()->Get_HP() > _pUser->Get_Stat()->Get_HP())
	{
		//��ġ�� ����
		_pUser->Get_CurStat()->Set_HP(_pUser->Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Name() << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	Set_Color(GRAY);

	system("pause");
}