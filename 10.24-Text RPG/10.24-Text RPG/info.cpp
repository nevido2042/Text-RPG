#include "pch.h"
#include "info.h"
#include "misc.h"
//#include "TextRPG.h"

//tagInfo::tagInfo()
//{
//}

CInfo::CInfo()
{
	//cout << m_szName << __FUNCTION__ << endl;
	//system("pause");
}

char* CInfo::Get_Name()
{
	return m_szName;
}

CStat* CInfo::Get_Stat()
{
	return &m_Stat;
}

CStat* CInfo::Get_CurStat()
{
	return &m_CurStat;
}

CInven* CInfo::Get_Inven()
{
	return &m_Inven;
}

int CInfo::Get_Gold()
{
	return m_iGold;
}

int CInfo::Get_Day()
{
	return m_iDay;
}

void CInfo::Set_Day(int _iDay)
{
	m_iDay = _iDay;
}

void CInfo::IncreaseDay()
{
	++m_iDay;
}

void CInfo::AddGold(int _iGold)
{
	m_iGold += _iGold;
}

void CInfo::RenderStat()
{
	cout << "체력: ";
	SetPrintColor(DARK_RED);
	for (int i = 0; i < Get_CurStat()->Get_HP(); ++i)
	{
		cout << "■";
	}

	int iEmptyCount = Get_Stat()->Get_HP() - Get_CurStat()->Get_HP();
	for (int i = 0; i <iEmptyCount ; ++i)
	{
		if (i >= Get_Stat()->Get_HP())
			break;

		cout << "□";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "마나: ";
	SetPrintColor(DARK_BLUE);
	for (int i = 0; i < Get_CurStat()->Get_MP(); ++i)
	{
		cout << "★";
	}
	for (int i = 0; i < Get_Stat()->Get_MP() - Get_CurStat()->Get_MP(); ++i)
	{
		if (i >= Get_Stat()->Get_MP())
			break;

		cout << "☆";
	}
	SetPrintColor(GRAY);
	cout << endl;

	cout << "공격력: ";
	SetPrintColor(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->Get_STR(); ++i)
	{
		cout << "†";
	}
	SetPrintColor(GRAY);
	cout << endl;
}

void CInfo::PrintName()
{
	cout << "이름: " << m_szName << endl;
	cout << endl;
}

void CInfo::PrintInfo()
{
	PrintName();
	//cout << "--------------------" << endl;
	RenderStat();
	Get_CurStat()->PrintDetailStat();
	cout << endl;
}

void CInfo::ResetStat()
{
	Get_CurStat()->Set_HP(Get_Stat()->Get_HP());
	Get_CurStat()->Set_MP(Get_Stat()->Get_MP());
	Get_CurStat()->Set_STR(Get_Stat()->Get_STR());
	Get_CurStat()->Set_DEX(Get_Stat()->Get_DEX());
	Get_CurStat()->Set_LUK(Get_Stat()->Get_LUK());
	Get_CurStat()->Set_INT(Get_Stat()->Get_INT());
}

void CInfo::Try_Attack(CInfo* _pTarget)
{
	SetPrintColor(YELLOW);
	cout << Get_Name() << "의 공격" << endl;
	SetPrintColor(GRAY);

	int AttackerDice = Roll_Dice(Get_CurStat()->Get_DEX());
	int TargetDice = _pTarget ->Roll_Dice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-Get_CurStat()->Get_STR());
		SetPrintColor(RED);
		cout << Get_Name() << "의 공격 명중." << endl;
		SetPrintColor(GRAY);
		cout << endl;

		int AttackerDice_LUK = Roll_Dice(Get_CurStat()->Get_LUK());
		int TargetDice_LUK = _pTarget->Roll_Dice(_pTarget->Get_CurStat()->Get_LUK());

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;

			_pTarget->Get_CurStat()->Add_HP(-Get_CurStat()->Get_STR());
			SetPrintColor(RED);
			cout << Get_Name() << "의 공격이 급소에 명중." << endl;
			SetPrintColor(GRAY);

			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;
		SetPrintColor(YELLOW);
		cout << Get_Name() << "의 공격 빗나감." << endl;
		SetPrintColor(GRAY);
		cout << endl;
		system("pause");
	}
}

int CInfo::Roll_Dice(int _iValue)
{
	if (_iValue == 0)
		return 0;

	return rand() % _iValue + 1;
}
