#include "pch.h"
#include "item_List.h"

//CRedPotion g_RedPotion("���� ����", 50);
//CSmall_RedPotion g_Small_RedPotion("���� ���� ����", 20);
//CSword_Of_Legend g_Sword_Of_Legend("������ ��", 999);

CRedPotion::CRedPotion(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CRedPotion::Use(CInfo* _pUser, CInfo* _pTarget)
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

CSmall_RedPotion::CSmall_RedPotion(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CSmall_RedPotion::Use(CInfo* _pUser, CInfo* _pTarget)
{
	//ȸ����
	const int Amount(1);

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

CSword_Of_Legend::CSword_Of_Legend(const char* _szName, int _iValue)
	:CItem(_szName, _iValue)
{
}

void CSword_Of_Legend::Use(CInfo* _pUser, CInfo* _pTarget)
{
	cout << "��� �� �� ���� ������ �Դϴ�." << endl;
	system("pause");
	return;
}
