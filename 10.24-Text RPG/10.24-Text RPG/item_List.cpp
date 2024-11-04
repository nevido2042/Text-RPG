#include "pch.h"
#include "item_List.h"

//CRedPotion g_RedPotion("빨간 물약", 50);
//CSmall_RedPotion g_Small_RedPotion("작은 빨간 물약", 20);
//CSword_Of_Legend g_Sword_Of_Legend("전설의 검", 999);

CRedPotion::CRedPotion(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CRedPotion::Use(CInfo* _pUser, CInfo* _pTarget)
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

CSmall_RedPotion::CSmall_RedPotion(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CSmall_RedPotion::Use(CInfo* _pUser, CInfo* _pTarget)
{
	//회복량
	const int Amount(1);

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

CSword_Of_Legend::CSword_Of_Legend(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CSword_Of_Legend::Use(CInfo* _pUser, CInfo* _pTarget)
{
	cout << "사용 할 수 없는 아이템 입니다." << endl;
	system("pause");
	return;
}
