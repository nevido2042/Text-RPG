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
	CInfo* pMerchant(nullptr);
	pMerchant = new CInfo;
	pMerchant->Get_Inven()->SetMerchantInven();

	//int iInput(0);

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
			pMerchant->Get_Inven()->SetMerchantInven();
			break;

		case 2:
			//모험
			if (_pPlayer->Get_CurStat()->Get_HP() == 0)
			{
				cout << "휴식이 필요." << endl;
				system("pause");
				continue;
			}

			SelectDungeon(_pPlayer);

			break;

		case 3:
			//소지품
			system("cls");
			_pPlayer->ResetStat();
			_pPlayer->Get_Inven()->PrintAll();
			system("pause");
			break;
		case 4:
			//상점
			OpenShop(_pPlayer, pMerchant);
			break;
		case 5:
			//저장&종료
			SaveCharacter(_pPlayer);
			SAFE_DELETE(_pPlayer);
			SAFE_DELETE(pMerchant);
			return;
		case 999:
			//치트
			_pPlayer->AddGold(999);
			extern CItem redPotion;
			_pPlayer->Get_Inven()->AddItem(redPotion);
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
