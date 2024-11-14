#include "pch.h"
#include "item_List.h"

//CRedPotion g_RedPotion("빨간 물약", 50);
//CSmall_RedPotion g_Small_RedPotion("작은 빨간 물약", 20);
//CSword_Of_Legend g_Sword_Of_Legend("전설의 검", 999);

CRedPotion::CRedPotion()
{
	strcpy_s(m_szName, "빨간 포션");
	m_iValue = 50;
}

int CRedPotion::Use(CEntity* _pUser, CEntity* _pTarget)
{
	//회복량
	const int Amount(3);

	_pUser->Get_Info().Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_Info().Get_CurStat()->Get_HP() > _pUser->Get_Info().Get_Stat()->Get_HP())
	{
		//과치유 방지
		_pUser->Get_Info().Get_CurStat()->Set_HP(_pUser->Get_Info().Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Info().Get_Name() << " 은(는) " << Amount << "만큼 회복 되었다." << endl;
	Set_Color(GRAY);

	system("pause");

	return SUCCESS;
}

CSmall_RedPotion::CSmall_RedPotion()
{
	strcpy_s(m_szName, "작은 빨간 포션");
	m_iValue = 20;
}

int CSmall_RedPotion::Use(CEntity* _pUser, CEntity* _pTarget)
{
	//회복량
	const int Amount(1);

	_pUser->Get_Info().Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_Info().Get_CurStat()->Get_HP() > _pUser->Get_Info().Get_Stat()->Get_HP())
	{
		//과치유 방지
		_pUser->Get_Info().Get_CurStat()->Set_HP(_pUser->Get_Info().Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Info().Get_Name() << " 은(는) " << Amount << "만큼 회복 되었다." << endl;
	Set_Color(GRAY);

	system("pause");

	return SUCCESS;
}

CSword_Of_Legend::CSword_Of_Legend()
{
	strcpy_s(m_szName, "전설의 검");
	m_iValue = 500;
}

int CSword_Of_Legend::Equip(CEntity* _pUser)
{
	const int Amount(3);

	CStat* CurStat = _pUser->Get_Info().Get_CurStat();
	CurStat->Set_AddSTR(CurStat->Get_AddSTR() + Amount);

	return SUCCESS;
}

int CSword_Of_Legend::Unequip(CEntity* _pUser)
{
	const int Amount(3);

	CStat* CurStat = _pUser->Get_Info().Get_CurStat();
	CurStat->Set_AddSTR(CurStat->Get_AddSTR() - Amount);

	return SUCCESS;

	return 0;
}
