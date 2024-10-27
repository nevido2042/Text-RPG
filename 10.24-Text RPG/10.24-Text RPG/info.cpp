#include "pch.h"
#include "info.h"
#include "misc.h"

CInfo::CInfo()
{
	ZeroMemory(m_szName, sizeof(m_szName));
	m_iDay = 1;
	m_iGold = 0;

	ZeroMemory(&m_Stat, sizeof(CStat));
	ZeroMemory(&m_CurStat, sizeof(CStat));
	ZeroMemory(&m_Inven, sizeof(CInven));
}

CInfo::~CInfo()
{
	Release();
}

void CInfo::Initialize()
{
	Get_Inven()->Initialize();
	Get_CurStat()->Initialize();
	Get_Stat()->Initialize();
}

void CInfo::Update()
{
}

void CInfo::Release()
{
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
	cout << "ü��: ";
	Set_Color(DARK_RED);
	for (int i = 0; i < Get_CurStat()->Get_HP(); ++i)
	{
		cout << "��";
	}

	int iEmptyCount = Get_Stat()->Get_HP() - Get_CurStat()->Get_HP();
	for (int i = 0; i <iEmptyCount ; ++i)
	{
		if (i >= Get_Stat()->Get_HP())
			break;

		cout << "��";
	}
	Set_Color(GRAY);
	cout << endl;

	cout << "����: ";
	Set_Color(DARK_BLUE);
	for (int i = 0; i < Get_CurStat()->Get_MP(); ++i)
	{
		cout << "��";
	}
	for (int i = 0; i < Get_Stat()->Get_MP() - Get_CurStat()->Get_MP(); ++i)
	{
		if (i >= Get_Stat()->Get_MP())
			break;

		cout << "��";
	}
	Set_Color(GRAY);
	cout << endl;

	cout << "���ݷ�: ";
	Set_Color(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->Get_STR(); ++i)
	{
		cout << "��";
	}
	Set_Color(GRAY);
	cout << endl;
}

void CInfo::PrintName()
{
	cout << "�̸�: " << m_szName << endl;
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
	Set_Color(YELLOW);
	cout << Get_Name() << "�� ����" << endl;
	Set_Color(GRAY);

	int AttackerDice = Roll_Dice(Get_CurStat()->Get_DEX());
	int TargetDice = _pTarget ->Roll_Dice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-Get_CurStat()->Get_STR());
		Set_Color(RED);
		cout << Get_Name() << "�� ���� ����." << endl;
		Set_Color(GRAY);
		cout << endl;

		int AttackerDice_LUK = Roll_Dice(Get_CurStat()->Get_LUK());
		int TargetDice_LUK = _pTarget->Roll_Dice(_pTarget->Get_CurStat()->Get_LUK());

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;

			_pTarget->Get_CurStat()->Add_HP(-Get_CurStat()->Get_STR());
			Set_Color(RED);
			cout << Get_Name() << "�� ������ �޼ҿ� ����." << endl;
			Set_Color(GRAY);

			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;
		Set_Color(YELLOW);
		cout << Get_Name() << "�� ���� ������." << endl;
		Set_Color(GRAY);
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

int CInfo::Select_Item(CInputManager* _InputManager, CInfo* _pTarget)
{
	//Render_Battle_Info();

	while ((true))
	{
		//Render_Battle_Info();

		Get_Inven()->PrintAll();
		cout << "����� ������ ����(���=0): ";
		if (_InputManager->Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (_InputManager->Get_Input() == 0)
		{
			return CANCLE;
		}

		//������ ��� �����۰�
		//�ҷ������ ���� ��������
		//�Լ� ������ ���� �޶� ������.
		// 
		//�ҷ� ���� �Ҷ� �ٽ� ��ƾ��ϳ�?
		CItem selectedItem = Get_Inven()->Get_ItemArray()[_InputManager->Get_Input() - 1];
		selectedItem.Use(this, _pTarget);

		//Render_Battle_Info();

		return SUCCESS;
	}
}
