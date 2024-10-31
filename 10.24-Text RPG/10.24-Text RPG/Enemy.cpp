#include "pch.h"
#include "Enemy.h"

CEnemy::CEnemy()
	:m_pInfo(nullptr)
{
    //m_pInfo = nullptr;
}

CEnemy::~CEnemy()
{
    Release();
}

CInfo& CEnemy::Get_Info()
{
    return *m_pInfo;
}

void CEnemy::Set_Info(CInfo* _pInfo)
{
    m_pInfo = _pInfo;
}

void CEnemy::Initialize()
{
    Set_Info(new CInfo);
    Get_Info().Initialize();
}

void CEnemy::Release()
{
    SAFE_DELETE(m_pInfo);
}

void CEnemy::Try_Attack(CPlayer* _pTarget)
{
	Set_Color(YELLOW);
	cout << Get_Info().Get_Name() << "의 공격" << endl;
	Set_Color(GRAY);

	int AttackerDice = Roll_Dice(Get_Info().Get_CurStat()->Get_DEX());
	int TargetDice = _pTarget->Roll_Dice(_pTarget->Get_Info().Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << Get_Info().Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Info().Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_Info().Get_CurStat()->Add_HP(-Get_Info().Get_CurStat()->Get_STR());
		Set_Color(RED);
		cout << Get_Info().Get_Name() << "의 공격 명중." << endl;
		Set_Color(GRAY);
		cout << endl;

		int AttackerDice_LUK = Roll_Dice(Get_Info().Get_CurStat()->Get_LUK());
		int TargetDice_LUK = _pTarget->Roll_Dice(_pTarget->Get_Info().Get_CurStat()->Get_LUK());

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << Get_Info().Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->Get_Info().Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;

			_pTarget->Get_Info().Get_CurStat()->Add_HP(-Get_Info().Get_CurStat()->Get_STR());
			Set_Color(RED);
			cout << Get_Info().Get_Name() << "의 공격이 급소에 명중." << endl;
			Set_Color(GRAY);

			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << Get_Info().Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Info().Get_Name() << " Dice_DEX: " << TargetDice << endl;
		Set_Color(YELLOW);
		cout << Get_Info().Get_Name() << "의 공격 빗나감." << endl;
		Set_Color(GRAY);
		cout << endl;
		system("pause");
	}
}

int CEnemy::Roll_Dice(int _iValue)
{
	if (_iValue == 0)
		return 0;

	return rand() % _iValue + 1;
}
