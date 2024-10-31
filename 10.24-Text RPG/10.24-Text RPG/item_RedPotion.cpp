#include "pch.h"
#include "item_List.h"

#include "info.h"

void RecoveryHP(CInfo* _pUser, CInfo* _pTarget)
{
	//회복량
	const int Amount(3);

	_pUser->Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_CurStat()->Get_HP() > _pUser->Get_Stat()->Get_HP())
	{
		//과치유 방지
		_pUser->Get_CurStat()->Set_HP(_pUser->Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Name() << " 은(는) " << Amount << "만큼 회복 되었다." << endl;
	Set_Color(GRAY);

	system("pause");
}