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

		cout << "[���� �޴�]" << endl;
		cout << endl;

		LINE_LINE;
		cout << " [1] ���ο� ����" << endl;
		cout << " [2] ���� ����" << endl;
		cout << " [3] �̾��ϱ�(����: �Ľ� �ʿ�?)" << endl;
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
			cout << "�÷��̾� ���� ����" << endl;
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

	//�κ��丮 ������, �Ҵ�, ������ ȣ�� ��
	//�� �Լ� �ּ� ����־ ��������.

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "./Save.txt", "rb") == 0)
	{//���� ã�� ����
		size_t iResult(0);
		iResult = fread(&Get_Player(), sizeof(CPlayer), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "�ҷ����� ����" << endl;
			system("pause");
		}

		fclose(pLoadFile);

		//�ε����Ͽ� ���� �ּҰ� ��� �־ ������ ���� �ߴ� �� ����.
		Get_Player().Get_Info().Get_Inven()->Initialize();
		//Get_Player().Initialize();

	}
	else
	{
		cout << "���� ���� ã�� ����." << endl;
		system("pause");
	}
}

void CMainGame::Input_Name()
{
	while (true)
	{
		system("cls");
		cout << "<ĳ���� ����>" << endl;
		LINE_LINE;

		cout << "�̸�" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> Get_Player().Get_Info().Get_Name(); //������ ���ΰ�? //�׷��� ������� �ι�� �� �ϴ�

		if (strlen(Get_Player().Get_Info().Get_Name()) >= NAME_LEN)
		{
			cout << "�̸� ���� �ʰ�!" << endl;
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
		cout << "<�ɷ�ġ ����>" << endl;

		Get_Player().Get_Info().PrintName();
		Get_Player().Get_Info().Get_Stat()->PrintALL();

		LINE_LINE;

		cout << "[1] �ֻ��� ������" << endl;
		cout << "[2] ����" << endl;
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
	{//�� ���� ���� ����

		size_t iResult(0);
		iResult = fwrite(&Get_Player(), sizeof(CPlayer), 1, pSaveFile);
		if (iResult != 1)//fwirte�� ī��Ʈ�� ��ȯ �ϴ±���
		{
			cout << "iResult: " << iResult << endl;
			//cout << "CInfo: " << sizeof(CInfo) << endl;

			cout << "���� ���� ����" << endl;
			system("pause");
		}

		fclose(pSaveFile);
		cout << "���� �Ϸ�!" << endl;
		system("pause");
	}
	else
	{
		cout << "�������!" << endl;
		cout << "�� ���� ���� ����" << endl;
		system("pause");
	}
}
