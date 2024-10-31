#include "pch.h"
#include "MainGame.h"
#include "Dungeon.h"

CPlayer& CMainGame::Get_Player()
{
	return *m_pPlayer;
}

void CMainGame::Set_Player(CPlayer* _pPlayer)
{
	if (m_pPlayer != nullptr)
	{
		PRINT_ERROR;
	}

	m_pPlayer = _pPlayer;

	Get_Player().Initialize();
}

CMerchant& CMainGame::Get_Merchant()
{
	return *m_pMerchant;
}

void CMainGame::Set_Merchant(CMerchant* _pMerchant)
{
	if (m_pMerchant != nullptr)
	{
		PRINT_ERROR;
	}

	m_pMerchant = _pMerchant;
	Get_Merchant().Initialize();
}

CInputManager& CMainGame::Get_InputManager()
{
	return *m_pInputManager;
}

void CMainGame::Set_InputManager(CInputManager* _pInputManager)
{
	if (m_pInputManager != nullptr)
	{
		PRINT_ERROR;
	}

	m_pInputManager = _pInputManager;
}

CMainGame::CMainGame()
	:m_pInputManager(nullptr), m_pPlayer(nullptr), m_pMerchant(nullptr)
{
	//m_pInputManager = nullptr;

	//m_pPlayer = nullptr;

	//m_pMerchant = nullptr;
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
		cout << " [3] 이어하기(고장: 파싱 필요?)" << endl;
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

void CMainGame::Load_Player()
{
	Set_Player(new CPlayer);

	//인벤토리 아이템, 할당, 생성자 호출 후
	//옛 함수 주소 집어넣어서 문제였다.

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "./Save.txt", "rb") == 0)
	{//파일 찾기 성공
		size_t iResult(0);
		iResult = fread(&Get_Player(), sizeof(CPlayer), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "불러오기 오류" << endl;
			system("pause");
		}

		fclose(pLoadFile);

		//로드파일에 옛날 주소가 담겨 있어서 엑세스 에러 뜨는 거 같다.
		Get_Player().Get_Info().Get_Inven()->Initialize();
		//Get_Player().Initialize();

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

void CMainGame::Save_Player()
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "./Save.txt", "wb") == 0)
	{//새 파일 생성 성공

		size_t iResult(0);
		iResult = fwrite(&Get_Player(), sizeof(CPlayer), 1, pSaveFile);
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
