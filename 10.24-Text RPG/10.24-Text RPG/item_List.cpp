#include "pch.h"
#include "item_List.h"

//CRedPotion g_RedPotion("���� ����", 50);
//CSmall_RedPotion g_Small_RedPotion("���� ���� ����", 20);
//CSword_Of_Legend g_Sword_Of_Legend("������ ��", 999);

CRedPotion::CRedPotion()
{
	strcpy_s(m_szName, "���� ����");
	m_iValue = 50;
}

int CRedPotion::Use(CEntity* _pUser, CEntity* _pTarget)
{
	//ȸ����
	const int Amount(3);

	_pUser->Get_Info().Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_Info().Get_CurStat()->Get_HP() > _pUser->Get_Info().Get_Stat()->Get_HP())
	{
		//��ġ�� ����
		_pUser->Get_Info().Get_CurStat()->Set_HP(_pUser->Get_Info().Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Info().Get_Name() << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	Set_Color(GRAY);

	system("pause");

	return SUCCESS;
}

CSmall_RedPotion::CSmall_RedPotion()
{
	strcpy_s(m_szName, "���� ���� ����");
	m_iValue = 20;
}

int CSmall_RedPotion::Use(CEntity* _pUser, CEntity* _pTarget)
{
	//ȸ����
	const int Amount(1);

	_pUser->Get_Info().Get_CurStat()->Add_HP(Amount);
	if (_pUser->Get_Info().Get_CurStat()->Get_HP() > _pUser->Get_Info().Get_Stat()->Get_HP())
	{
		//��ġ�� ����
		_pUser->Get_Info().Get_CurStat()->Set_HP(_pUser->Get_Info().Get_Stat()->Get_HP());
	}
	Set_Color(YELLOW);
	cout << _pUser->Get_Info().Get_Name() << " ��(��) " << Amount << "��ŭ ȸ�� �Ǿ���." << endl;
	Set_Color(GRAY);

	system("pause");

	return SUCCESS;
}

CSword_Of_Legend::CSword_Of_Legend()
{
	strcpy_s(m_szName, "������ ��");
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
