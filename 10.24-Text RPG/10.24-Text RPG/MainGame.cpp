#include "pch.h"
#include "MainGame.h"

int& CMainGame::Get_Input()
{
	return m_iInput;
}

void CMainGame::Set_Input(int _iInput)
{
	m_iInput = _iInput;
}

CInfo& CMainGame::Get_Player()
{
	return *m_pPlayer;
}

void CMainGame::Set_Player(CInfo* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

CInfo& CMainGame::Get_Merchant()
{
	return *m_pMerchant;
}

void CMainGame::Set_Merchant(CInfo* _pMerchant)
{
	m_pMerchant = _pMerchant;
}

CInfo& CMainGame::Get_Enemy()
{
	return *m_Enemy;
}

void CMainGame::Set_Enemy(CInfo* _pEnemy)
{
	m_Enemy = _pEnemy;
}

CMainGame::CMainGame()
{
	//cout << __FUNCTION__ << endl;
	//system("pause");
	srand(unsigned(time(NULL)));

	m_iInput = 0;

	m_pPlayer = nullptr;
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
}

void CMainGame::Update()
{
}

void CMainGame::Release()
{
}

void CMainGame::Print_MainMenu()
{
	while (true)
	{
		system("cls");
		cout << "<TEXT RPG>" << endl;
		cout << endl;

		cout << "[메인 메뉴]" << endl;
		cout << endl;

		cout << "1.새 게임 2.게임종료 3.이어하기" << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			Create_Player();
			break;
		case 2:
			return;

		case 3:
			Load_Player();
			break;

		default:
			cout << "default";
			break;
		}

		if (&Get_Player())
		{
			//Get_Player().Select_Task(); //이 함수를 플레이어 한테 줘야하나
			Select_Task(); 
		}
		else
		{
			cout << "플레이어 생성 실패" << endl;
			system("pause");
		}
	}
}

int CMainGame::Receive_Input()
{
	cout << "입력: ";
	cin >> Get_Input();

	int iTemp = Check_Input();
	if (iTemp == INPUT_ERROR)
	{
		return INPUT_ERROR;
	}

	return SUCCESS;
}

int CMainGame::Check_Input()
{
	if (!cin) //자료형이 다른 값이 들어 오는 지 체크
	{
		cin.clear();

		while (cin.get() != '\n');

		//cout << "잘못된 입력" << endl;
		//system("pause");

		return INPUT_ERROR;
	}

	return SUCCESS;
}

void CMainGame::Create_Player()
{
	Set_Player(new CInfo);
	Input_Name();
}

void CMainGame::Select_Task()
{
	//상인도 나중에 처리하자
	Set_Merchant(new CInfo);
	Get_Merchant().Get_Inven()->SetMerchantInven();

	while (true)
	{
		system("cls");
		Get_Player().PrintInfo();

		SetPrintColor(YELLOW);
		cout << Get_Player().Get_Gold() << 'G' << endl;
		SetPrintColor(GRAY);

		cout << "Day-" << Get_Player().Get_Day() << endl;
		cout << "현재위치: 은신처" << endl;
		cout << "<행동 결정>" << endl;
		cout << " 1.휴식 2.모험 3.소지품 4.상점 5.저장&종료 999.치트" << endl;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			//휴식
			Get_Player().ResetStat();
			Get_Player().IncreaseDay();
			Get_Merchant().Get_Inven()->SetMerchantInven();
			break;

		case 2:
			//모험
			if (Get_Player().Get_CurStat()->Get_HP() == 0)
			{
				cout << "휴식이 필요." << endl;
				system("pause");
				continue;
			}

			Select_Dungeon();

			break;

		case 3:
			//소지품
			system("cls");
			Get_Player().ResetStat();
			Get_Player().Get_Inven()->PrintAll();
			system("pause");
			break;
		case 4:
			//상점
			Open_Shop();
			break;
		case 5:
			//저장&종료
			Save_Player();
			SAFE_DELETE(m_pPlayer);
			SAFE_DELETE(m_pMerchant);
			return;
		case 999:
			//치트
			Get_Player().AddGold(999);
			extern CItem redPotion;
			Get_Player().Get_Inven()->AddItem(redPotion);
			break;
		default:
			break;
		}
	}
}

void CMainGame::Load_Player()
{
	Set_Player(new CInfo);

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "../Data/Save.txt", "rb") == 0)
	{//파일 찾기 성공
		size_t iResult(0);
		iResult = fread(&Get_Player(), sizeof(CInfo), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "불러오기 오류" << endl;
			system("pause");
		}

		fclose(pLoadFile);
	}
	else
	{
		cout << "저장 파일 찾지 못함." << endl;
		system("pause");
	}
}

void CMainGame::Input_Name()
{
	while (true)
	{
		system("cls");
		//cout << "====================" << endl;
		cout << "<캐릭터 생성>" << endl;
		cout << endl;

		cout << "이름" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> Get_Player().Get_Name(); //위험한 짓인가? //그래서 저장공간 두배로 함 일단

		if (strlen(Get_Player().Get_Name()) >= NAME_LEN)
		{
			cout << "이름 길이 초과!" << endl;
			//cout << sizeof((*_ppPlayer)->szName) << endl;
			system("pause");
			continue;
		}

		break;
	}
}

void CMainGame::Select_Dungeon()
{
	while (true)
	{
		if (Get_Player().Get_CurStat()->Get_HP() == 0)
		{
			return;
		}

		system("cls");
		Get_Player().PrintInfo();
		cout << "현재위치: 갈래길" << endl;
		cout << "<모험 장소 선택>" << endl;
		cout << "1.초원 2.산 3.동굴 4.복귀" << endl;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			//Enter_Grassland(_pPlayer);
			Enter_Dungeon(Grassland);
			break;
		case 2:
			//Enter_Mountain(Get_Player());
			Enter_Dungeon(Mountain);
			break;
		case 3:
			//Enter_Cave(Get_Player());
			Enter_Dungeon(Cave);
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

void CMainGame::Open_Shop()
{
	while (true)
	{
		Render_Shop();

		cout << "1.구매 2.판매 3.나가기" << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			Buy_Item();
			break;
		case 2:
			Sell_Item();
			break;
		case 3:
			//SAFE_DELETE(merchant);
			return;
		default:
			break;
		}
	}
}

void CMainGame::Buy_Item()
{
	while (true)
	{
		Render_Shop();

		cout << "사고싶은 품목의 번호를 선택(취소=0)" << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (Get_Input() == 0)
		{
			break;
		}

		CItem item = Get_Merchant().Get_Inven()->Get_ItemArray()[Get_Input() - 1];

		int iItemValue = Get_Merchant().Get_Inven()->Get_ItemArray()[Get_Input() - 1].Get_Value();
		if (Get_Player().Get_Gold() >= iItemValue)
		{
			Get_Player().AddGold(-iItemValue);
		}
		else
		{
			cout << "소지금이 부족합니다." << endl;
			system("pause");
			continue;
		}

		if (Get_Merchant().Get_Inven()->RemoveItem(Get_Input() - 1) == SUCCESS)
		{
			Get_Player().Get_Inven()->AddItem(item);
		}
	}
}

void CMainGame::Sell_Item()
{
	while (true)
	{
		Render_Shop();

		cout << "팔고싶은 품목의 번호를 선택(취소=0)" << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (Get_Input() == 0)
		{
			break;
		}

		CItem item = Get_Player().Get_Inven()->Get_ItemArray()[Get_Input() - 1];
		if (Get_Player().Get_Inven()->RemoveItem(Get_Input() - 1) == SUCCESS)
		{
			Get_Player().AddGold(item.Get_Value());
			Get_Merchant().Get_Inven()->AddItem(item);
		}
	}
}

void CMainGame::Render_Shop()
{
	system("cls");

	SetPrintColor(YELLOW);
	cout << Get_Player().Get_Gold() << "G" << endl;
	SetPrintColor(GRAY);

	cout << "플레이어의 ";
	Get_Player().Get_Inven()->PrintAll();

	cout << "===============================" << endl;

	cout << "상인의";
	Get_Merchant().Get_Inven()->PrintAll();
	cout << endl;
}

void CMainGame::Save_Player()
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//새 파일 생성 성공

		size_t iResult(0);
		iResult = fwrite(&Get_Player(), sizeof(CInfo), 1, pSaveFile);
		if (iResult != 1)//fwirte는 카운트를 반환 하는구나
		{
			cout << "iResult: " << iResult << endl;
			//cout << "CInfo: " << sizeof(CInfo) << endl;

			cout << "파일 쓰기 오류" << endl;
			system("pause");
		}

		fclose(pSaveFile);
		cout << "저장 완료!" << endl;
		system("pause");
	}
	else
	{
		cout << "저장실패!" << endl;
		cout << "새 파일 생성 실패" << endl;
		system("pause");
	}
}

void CMainGame::Enter_Dungeon(int _iValue)
{
	while (true)
	{
		if (Get_Player().Get_CurStat()->Get_HP() == 0)
		{
			//cout << "플레이어 쓰러짐" << endl;
			//system("pause");
			return;
		}

		system("cls");
		Get_Player().PrintInfo();

		switch (_iValue)
		{
		case Grassland:
			SetPrintColor(GREEN);
			cout << "현재 위치: 초원" << endl;
			SetPrintColor(GRAY);
			break;
		case Mountain:
			SetPrintColor(YELLOW);
			cout << "현재 위치: 산" << endl;
			SetPrintColor(GRAY);
			break;
		case Cave:
			SetPrintColor(RED);
			cout << "현재 위치: 동굴" << endl;
			SetPrintColor(GRAY);
			break;
		}

		cout << "[행동 선택]" << endl;
		cout << "1.대기 2.탐색 3.복귀" << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}
		switch (Get_Input())
		{
		case 1:
			//대기
			//_pPlayer->ResetStat();
			Get_Player().Get_CurStat()->Add_HP(-1);

			break;
		case 2:
			//탐색
			//적 조우, 함정(DEX), 상자(INT)-미믹,보물,함정
			Trigger_Random_Event(_iValue);
			//FaceMonster(_pPlayer, 2);
			break;
		case 3:
			//복귀
			return;
		default:
			break;
		}

	}
}

void CMainGame::Trigger_Random_Event(int _iValue)
{
	const int iEventCount = 3;
	int iRandNum = rand() % iEventCount + 1;

	switch (iRandNum)
	{
	case 1:
		Face_Enemy(_iValue);
		return;
	case 2:
		Trigger_Trap(_iValue);
		return;
	case 3:
		Find_Magic_Box(_iValue);
		return;
	default:
		cout << __FUNCTION__ << endl;
		system("pause");
		break;
	}
}

void CMainGame::Face_Enemy(int _iValue)
{
	Set_Enemy(new CInfo);
	strcpy_s(Get_Enemy().Get_Name(), NAME_LEN, "???");
	Get_Enemy().Get_Stat()->SetStatRandom(_iValue);
	Get_Enemy().ResetStat();

	Render_Battle_Info();

	SetPrintColor(YELLOW);
	cout << "몬스터와 마주했다." << endl;
	SetPrintColor(GRAY);

	system("pause");

	Start_Battle();

	SAFE_DELETE(m_Enemy);

	return;
}

void CMainGame::Render_Battle_Info()
{
	system("cls");
	Get_Player().PrintInfo();
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	Get_Enemy().PrintInfo();
}

void CMainGame::Start_Battle()
{
	Render_Battle_Info();

	if (Get_Enemy().Get_CurStat()->Get_DEX() > Get_Player().Get_CurStat()->Get_DEX())
	{
		//_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "몬스터의 민첩이 더 높다." << endl;
		SetPrintColor(YELLOW);
		cout << "몬스터의 선제 공격!" << endl;
		SetPrintColor(GRAY);

		cout << endl;
		system("pause");

		Try_Attack(&Get_Enemy(), &Get_Player());
		Render_Battle_Info();

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Render_Battle_Info();
			
			Get_Player().Get_CurStat()->Set_HP(0);
			SetPrintColor(YELLOW);
			cout << "플레이어 쓰러짐!" << endl;
			SetPrintColor(GRAY);

			cout << endl;

			system("pause");

			return;
		}
	}

	while (true)
	{
		Render_Battle_Info();

		//cout << "몬스터를 발견함." << endl;
		cout << "[행동 선택]" << endl;
		cout << "1.공격 2.아이템 3.도망 " << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
		{
			//공격
			Try_Attack(&Get_Player(), &Get_Enemy());

			Render_Battle_Info();
			cout << endl;

			if (Get_Enemy().Get_CurStat()->Get_HP() <= 0)
			{
				Get_Enemy().Get_CurStat()->Set_HP(0);

				SetPrintColor(YELLOW);
				cout << "몬스터 쓰러짐!" << endl;
				SetPrintColor(GRAY);

				cout << "전투 종료" << endl;

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "Test Item");
				item.Set_Value(50);
				cout << "아이템 획득:" << item.Get_Name() << endl;
				Get_Player().Get_Inven()->AddItem(item);

				system("pause");
				return;
			}

			//system("pause");

			break;
		}

		case 2:
			//아이템
			if (Select_Item() == SUCCESS)
			{
				break;
			}
			else
			{
				continue;
			}
		case 3:
			//도망
		{
			int iPlayerDice = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());
			int iMonsterDice = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());

			if (iPlayerDice > iMonsterDice)
			{
				cout << "PlayerDice: " << iPlayerDice << endl;
				cout << "MonsterDice: " << iMonsterDice << endl;

				SetPrintColor(YELLOW);
				cout << "도망 성공" << endl;
				SetPrintColor(GRAY);

				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "MonsterDice: " << iMonsterDice << endl;
			SetPrintColor(YELLOW);
			cout << "도망 실패" << endl;
			SetPrintColor(GRAY);

			system("pause");
			break;
		}
		default:
			continue;
		}

		SetPrintColor(YELLOW);
		cout << "적의 턴" << endl;
		SetPrintColor(GRAY);
		cout << endl;

		system("pause");

		Render_Battle_Info();
		Try_Attack(&Get_Enemy(), &Get_Player());

		Render_Battle_Info();

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Get_Player().Get_CurStat()->Set_HP(0);

			SetPrintColor(YELLOW);
			cout << "플레이어 쓰러짐!" << endl;
			SetPrintColor(GRAY);

			cout << "전투 종료" << endl;
			system("pause");
			return;
		}
	}
}

void CMainGame::Try_Attack(CInfo* _pAttacker, CInfo* _pTarget)
{
	SetPrintColor(YELLOW);
	cout << _pAttacker->Get_Name() << "의 공격" << endl;
	SetPrintColor(GRAY);

	int AttackerDice = Roll_Dice(_pAttacker->Get_CurStat()->Get_DEX());
	int TargetDice = Roll_Dice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
		SetPrintColor(RED);
		cout << _pAttacker->Get_Name() << "의 공격 명중." << endl;
		SetPrintColor(GRAY);
		cout << endl;

		int AttackerDice_LUK = Roll_Dice(_pAttacker->Get_CurStat()->Get_LUK());
		int TargetDice_LUK = Roll_Dice(_pTarget->Get_CurStat()->Get_LUK());

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << _pAttacker->Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;

			_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
			SetPrintColor(RED);
			cout << _pAttacker->Get_Name() << "의 공격이 급소에 명중." << endl;
			SetPrintColor(GRAY);

			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;
		SetPrintColor(YELLOW);
		cout << _pAttacker->Get_Name() << "의 공격 빗나감." << endl;
		SetPrintColor(GRAY);
		cout << endl;
		system("pause");
	}
}

int CMainGame::Roll_Dice(int _iValue)
{
	if (_iValue == 0)
		return 0;

	return rand() % _iValue + 1;
}

int CMainGame::Select_Item()
{
	Render_Battle_Info();

	while ((true))
	{
		Render_Battle_Info();

		Get_Player().Get_Inven()->PrintAll();
		cout << "사용할 아이템 선택(취소=0): ";
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (Get_Input() == 0)
		{
			return _ERROR;
		}

		//게임중 얻는 아이템과
		//불러오기로 들어온 아이템의
		//함수 포인터 값이 달라서 터진다.
		// 
		//불러 오기 할때 다시 담아야하나?
		CItem selectedItem = Get_Player().Get_Inven()->Get_ItemArray()[Get_Input() - 1];
		selectedItem.Use(&Get_Player(), &Get_Enemy());

		Render_Battle_Info();

		return SUCCESS;
	}
}

void CMainGame::Trigger_Trap(int _iValue)
{
	system("cls");
	Get_Player().PrintInfo();

	SetPrintColor(YELLOW);
	cout << "함정(" << _iValue << ")이 작동되었다!" << endl;
	SetPrintColor(GRAY);

	cout << "주사위 굴리기(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());
	if (iDice_DEX > _iValue)
	{
		cout << "주사위 결과: " << iDice_DEX << endl;
		SetPrintColor(YELLOW);
		cout << "재빠른 몸놀림으로 함정을 피했다." << endl;
		SetPrintColor(GRAY);

		system("pause");
		return;
	}
	else
	{
		Get_Player().Get_CurStat()->Add_HP(-_iValue);

		cout << "주사위 결과: " << iDice_DEX << endl;
		SetPrintColor(RED);
		cout << "함정에 피해를 받았다." << endl;
		SetPrintColor(GRAY);

		system("pause");

		system("cls");
		Get_Player().PrintInfo();

		return;
	}
}

void CMainGame::Find_Magic_Box(int _iValue)
{

	while (true)
	{
		system("cls");
		Get_Player().PrintInfo();

		SetPrintColor(YELLOW);
		cout << "마법으로 잠긴 상자(" << _iValue << ")를 발견했다._" << endl;
		SetPrintColor(GRAY);

		cout << "1.마법 풀기(INT) 2.무시하기" << endl;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			//마법 풀기
		{
			int iDice_INT = Roll_Dice(Get_Player().Get_CurStat()->Get_INT());

			if (iDice_INT > _iValue)
			{
				cout << "주사위 결과: " << iDice_INT << endl;
				SetPrintColor(YELLOW);
				cout << "상자에 걸린 마법을 제거했다." << endl;
				cout << "보물을 획득 했다." << endl;
				SetPrintColor(GRAY);

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "보물");
				item.Set_Value(500);

				Get_Player().Get_Inven()->AddItem(item);

				system("pause");
			}
			else
			{
				cout << "주사위 결과: " << iDice_INT << endl;
				SetPrintColor(YELLOW);
				cout << "마법을 제거하지 못했다." << endl;
				SetPrintColor(GRAY);

				system("pause");
			}
			return;
		}
		case 2:
			//무시 하기
			return;
		default:
			break;
		}
	}
}
