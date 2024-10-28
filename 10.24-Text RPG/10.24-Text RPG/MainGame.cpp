#include "pch.h"
#include "MainGame.h"
#include "Dungeon.h"

CPlayer& CMainGame::Get_Player()
{
	return *m_pPlayer;
}

void CMainGame::Set_Player(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;

	Get_Player().Initialize();
}

CMerchant& CMainGame::Get_Merchant()
{
	return *m_pMerchant;
}

void CMainGame::Set_Merchant(CMerchant* _pMerchant)
{
	m_pMerchant = _pMerchant;
}

CInputManager& CMainGame::Get_InputManager()
{
	return *m_pInputManager;
}

void CMainGame::Set_InputManager(CInputManager* _pInputManager)
{
	m_pInputManager = _pInputManager;
}

CMainGame::CMainGame()
{
	m_pInputManager = nullptr;

	m_pPlayer = nullptr;

	m_pMerchant = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned(time(NULL)));
	Set_InputManager(new CInputManager);
}

void CMainGame::Update()
{
}

void CMainGame::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMerchant);
	SAFE_DELETE(m_pInputManager);
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

		LINE_LINE;
		cout << " [1] 새로운 게임" << endl;
		cout << " [2] 게임 종료" << endl;
		cout << " [3] 이어하기" << endl;
		LINE_LINE;

		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_InputManager().Get_Input())
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
			Set_Merchant(new CMerchant);
			Get_Merchant().Set_Merchant_Inven();

			int iResult = Get_Player().Select_Task(&Get_InputManager(), &Get_Merchant());

			if (iResult == SUCCESS)
			{
				Save_Player();
			}
			else
			{
				PRINT_ERROR;
			}

			SAFE_DELETE(m_pMerchant);
		}
		else
		{
			cout << "플레이어 생성 실패" << endl;
			system("pause");
		}
	}
}

void CMainGame::Create_Player()
{
	Set_Player(new CPlayer);
	Input_Name();
	Set_Random_STAT();
}

//void CMainGame::Select_Task()
//{
//	while (true)
//	{
//		system("cls");
//		Get_Player().Get_Info().PrintInfo();
//
//		Set_Color(YELLOW);
//		cout << Get_Player().Get_Info().Get_Gold() << 'G' << endl;
//		Set_Color(GRAY);
//
//		cout << "Day - " << Get_Player().Get_Info().Get_Day() << endl;
//		cout << "현재위치: 은신처" << endl;
//		LINE_LINE;
//		cout << " [1] 휴식" << endl;
//		cout << " [2] 모험" << endl;
//		cout << " [3] 소지품" << endl;
//		cout << " [4] 상점" << endl;
//		cout << " [5] 저장 & 종료" << endl;
//		cout << " [999] 치트" << endl;
//		LINE_LINE;
//
//
//		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//		{
//			continue;
//		}
//
//		switch (Get_InputManager().Get_Input())
//		{
//		case 1:
//			//휴식
//			Get_Player().Get_Info().ResetStat();
//			Get_Player().Get_Info().IncreaseDay();
//			Get_Merchant().Get_Inven()->SetMerchantInven();
//			break;
//
//		case 2:
//			//모험
//			if (Get_Player().Get_Info().Get_CurStat()->Get_HP() == 0)
//			{
//				cout << "휴식이 필요." << endl;
//				system("pause");
//				continue;
//			}
//
//			Select_Dungeon();
//
//			break;
//
//		case 3:
//			//소지품
//			system("cls");
//
//			Get_Player().Get_Info().Select_Item(&Get_InputManager(), nullptr);
//
//			break;
//		case 4:
//			//상점
//			Open_Shop();
//			break;
//		case 5:
//			//저장&종료
//			Save_Player();
//			SAFE_DELETE(m_pPlayer);
//			SAFE_DELETE(m_pMerchant);
//			return;
//		case 999:
//			//치트
//			Get_Player().Get_Info().AddGold(999);
//			extern CItem redPotion;
//			Get_Player().Get_Info().Get_Inven()->AddItem(redPotion);
//			break;
//		default:
//			break;
//		}
//	}
//}

void CMainGame::Load_Player()
{
	Set_Player(new CPlayer);

	//인벤토리 아이템, 할당, 생성자 호출 후
	//옛 함수 주소 집어넣어서 문제였다.

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

		Get_Player().Get_Info().Get_Inven()->Initialize();
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
		cout << "<캐릭터 생성>" << endl;
		LINE_LINE;

		cout << "이름" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> Get_Player().Get_Info().Get_Name(); //위험한 짓인가? //그래서 저장공간 두배로 함 일단

		if (strlen(Get_Player().Get_Info().Get_Name()) >= NAME_LEN)
		{
			cout << "이름 길이 초과!" << endl;
			//cout << sizeof((*_ppPlayer)->szName) << endl;
			system("pause");
			continue;
		}

		break;
	}
}

void CMainGame::Set_Random_STAT()
{
	Get_Player().Get_Info().Get_Stat()->SetStatRandom();

	while (true)
	{
		system("cls");
		cout << "<능력치 설정>" << endl;

		Get_Player().Get_Info().PrintName();
		Get_Player().Get_Info().Get_Stat()->PrintALL();

		LINE_LINE;

		cout << "[1] 주사위 굴리기" << endl;
		cout << "[2] 결정" << endl;
		LINE_LINE;

		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_InputManager().Get_Input())
		{
		case 1:
			Get_Player().Get_Info().Get_Stat()->SetStatRandom();
			continue;
		case 2:
			Get_Player().Get_Info().ResetStat();
			return;
		default:
			break;
		}
	}
}

//void CMainGame::Select_Dungeon()
//{
//	while (true)
//	{
//		if (Get_Player().Get_Info().Get_CurStat()->Get_HP() == 0)
//		{
//			return;
//		}
//
//		system("cls");
//		Get_Player().Get_Info().PrintInfo();
//		cout << "현재위치: 갈래길" << endl;
//		cout << "<모험 장소 선택>" << endl;
//		LINE_LINE;
//		Set_Color(GREEN);
//		cout << "[1] 초원 " << endl; // 2.산 3.동굴 4.복귀" << endl;
//		Set_Color(GRAY);
//
//		Set_Color(YELLOW);
//		cout << "[2] 산 " << endl;
//		Set_Color(GRAY);
//
//		Set_Color(RED);
//		cout << "[3] 동굴 " << endl;
//		Set_Color(GRAY);
//
//		cout << "[4] 은신처로 돌아가기 " << endl;
//		LINE_LINE;
//
//		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//		{
//			continue;
//		}
//
//		switch (Get_InputManager().Get_Input())
//		{
//		case 1:
//		{
//			CDungeon* Dungeon = new CDungeon(&Get_Player().Get_Info(), Grassland, &Get_InputManager());
//			Dungeon->Initialize();
//			SAFE_DELETE(Dungeon);
//			break;
//		}
//
//		case 2:
//		{
//			CDungeon* Dungeon = new CDungeon(&Get_Player().Get_Info(), Mountain, &Get_InputManager());
//			Dungeon->Initialize();
//			SAFE_DELETE(Dungeon);
//			break;
//		}
//			
//		case 3:
//		{
//			CDungeon* Dungeon = new CDungeon(&Get_Player().Get_Info(), Cave, &Get_InputManager());
//			Dungeon->Initialize();
//			SAFE_DELETE(Dungeon);
//			break;
//		}
//			
//		case 4:
//			return;
//		default:
//			break;
//		}
//	}
//}

//void CMainGame::Open_Shop()
//{
//	while (true)
//	{
//		Render_Shop();
//
//		cout << "현재위치: 상점" << endl;
//		LINE_LINE;
//		cout << "[1] 구매" << endl;
//		cout << "[2] 판매" << endl;
//		cout << "[3] 은신처로 돌아가기" << endl;
//		LINE_LINE;
//
//
//		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//		{
//			continue;
//		}
//
//		switch (Get_InputManager().Get_Input())
//		{
//		case 1:
//			Buy_Item();
//			break;
//		case 2:
//			Sell_Item();
//			break;
//		case 3:
//			//SAFE_DELETE(merchant);
//			return;
//		default:
//			break;
//		}
//	}
//}

//void CMainGame::Buy_Item()
//{
//	while (true)
//	{
//		Render_Shop();
//
//		cout << "사고싶은 품목의 번호를 선택(취소=0)" << endl;
//		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//		{
//			continue;
//		}
//
//		if (Get_InputManager().Get_Input() == 0)
//		{
//			break;
//		}
//
//		CItem item = Get_Merchant().Get_Inven()->Get_ItemArray()[Get_InputManager().Get_Input() - 1];
//
//		int iItemValue = Get_Merchant().Get_Inven()->Get_ItemArray()[Get_InputManager().Get_Input() - 1].Get_Value();
//		if (Get_Player().Get_Info().Get_Gold() >= iItemValue)
//		{
//			Get_Player().Get_Info().AddGold(-iItemValue);
//		}
//		else
//		{
//			cout << "소지금이 부족합니다." << endl;
//			system("pause");
//			continue;
//		}
//
//		if (Get_Merchant().Get_Inven()->RemoveItem(Get_InputManager().Get_Input() - 1) == SUCCESS)
//		{
//			Get_Player().Get_Info().Get_Inven()->AddItem(item);
//		}
//	}
//}

//void CMainGame::Sell_Item()
//{
//	while (true)
//	{
//		Render_Shop();
//
//		cout << "팔고싶은 품목의 번호를 선택(취소=0)" << endl;
//		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
//		{
//			continue;
//		}
//
//		if (Get_InputManager().Get_Input() == 0)
//		{
//			break;
//		}
//
//		CItem item = Get_Player().Get_Info().Get_Inven()->Get_ItemArray()[Get_InputManager().Get_Input() - 1];
//		if (Get_Player().Get_Info().Get_Inven()->RemoveItem(Get_InputManager().Get_Input() - 1) == SUCCESS)
//		{
//			Get_Player().Get_Info().AddGold(item.Get_Value());
//			Get_Merchant().Get_Inven()->AddItem(item);
//		}
//	}
//}

//void CMainGame::Render_Shop()
//{
//	system("cls");
//
//	cout << "보유 금화: ";
//	Set_Color(YELLOW);
//	cout << Get_Player().Get_Info().Get_Gold() << "G" << endl;
//	Set_Color(GRAY);
//
//	cout << "플레이어의 ";
//	Get_Player().Get_Info().Get_Inven()->PrintAll();
//
//	LINE;
//
//	cout << "상인의";
//	Get_Merchant().Get_Inven()->PrintAll();
//	cout << endl;
//}

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
