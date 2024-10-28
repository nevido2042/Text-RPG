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
	cout << "체력: ";
	Set_Color(DARK_RED);
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
	Set_Color(GRAY);
	cout << endl;

	cout << "마나: ";
	Set_Color(DARK_BLUE);
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
	Set_Color(GRAY);
	cout << endl;

	cout << "공격력: ";
	Set_Color(DAKR_YELLOW);
	for (int i = 0; i < Get_CurStat()->Get_STR(); ++i)
	{
		cout << "†";
	}
	Set_Color(GRAY);
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
	Set_Color(YELLOW);
	cout << Get_Name() << "의 공격" << endl;
	Set_Color(GRAY);

	int AttackerDice = Roll_Dice(Get_CurStat()->Get_DEX());
	int TargetDice = _pTarget ->Roll_Dice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-Get_CurStat()->Get_STR());
		Set_Color(RED);
		cout << Get_Name() << "의 공격 명중." << endl;
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
			cout << Get_Name() << "의 공격이 급소에 명중." << endl;
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
		cout << Get_Name() << "의 공격 빗나감." << endl;
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
		cout << "사용할 아이템 선택(취소=0): ";
		if (_InputManager->Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (_InputManager->Get_Input() == 0)
		{
			return CANCLE;
		}

		//게임중 얻는 아이템과
		//불러오기로 들어온 아이템의
		//함수 포인터 값이 달라서 터진다.
		// 
		//불러 오기 할때 다시 담아야하나?
		CItem selectedItem = Get_Inven()->Get_ItemArray()[_InputManager->Get_Input() - 1];
		selectedItem.Use(this, _pTarget);

		//Render_Battle_Info();

		return SUCCESS;
	}
}

//void CInfo::Select_Task()
//{
//	//while (true)
//	//{
//	//	system("cls");
//	//	Get_Player().PrintInfo();
//
//	//	Set_Color(YELLOW);
//	//	cout << Get_Player().Get_Gold() << 'G' << endl;
//	//	Set_Color(GRAY);
//
//	//	cout << "Day - " << Get_Player().Get_Day() << endl;
//	//	cout << "현재위치: 은신처" << endl;
//	//	LINE_LINE;
//	//	cout << " [1] 휴식" << endl;
//	//	cout << " [2] 모험" << endl;
//	//	cout << " [3] 소지품" << endl;
//	//	cout << " [4] 상점" << endl;
//	//	cout << " [5] 저장 & 종료" << endl;
//	//	cout << " [999] 치트" << endl;
//	//	LINE_LINE;
//
//
//	//	if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//	//	{
//	//		continue;
//	//	}
//
//	//	switch (Get_InputManager().Get_Input())
//	//	{
//	//	case 1:
//	//		//휴식
//	//		Get_Player().ResetStat();
//	//		Get_Player().IncreaseDay();
//	//		Get_Merchant().Get_Inven()->SetMerchantInven();
//	//		break;
//
//	//	case 2:
//	//		//모험
//	//		if (Get_Player().Get_CurStat()->Get_HP() == 0)
//	//		{
//	//			cout << "휴식이 필요." << endl;
//	//			system("pause");
//	//			continue;
//	//		}
//
//	//		Select_Dungeon();
//
//	//		break;
//
//	//	case 3:
//	//		//소지품
//	//		system("cls");
//
//	//		Get_Player().Select_Item(&Get_InputManager(), nullptr);
//
//	//		break;
//	//	case 4:
//	//		//상점
//	//		Open_Shop();
//	//		break;
//	//	case 5:
//	//		//저장&종료
//	//		Save_Player();
//	//		SAFE_DELETE(m_pPlayer);
//	//		SAFE_DELETE(m_pMerchant);
//	//		return;
//	//	case 999:
//	//		//치트
//	//		Get_Player().AddGold(999);
//	//		extern CItem redPotion;
//	//		Get_Player().Get_Inven()->AddItem(redPotion);
//	//		break;
//	//	default:
//	//		break;
//	//	}
//	//}
//}
