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

		cout << "[���� �޴�]" << endl;
		cout << endl;

		LINE_LINE;
		cout << " [1] ���ο� ����" << endl;
		cout << " [2] ���� ����" << endl;
		cout << " [3] �̾��ϱ�" << endl;
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
//		cout << "������ġ: ����ó" << endl;
//		LINE_LINE;
//		cout << " [1] �޽�" << endl;
//		cout << " [2] ����" << endl;
//		cout << " [3] ����ǰ" << endl;
//		cout << " [4] ����" << endl;
//		cout << " [5] ���� & ����" << endl;
//		cout << " [999] ġƮ" << endl;
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
//			//�޽�
//			Get_Player().Get_Info().ResetStat();
//			Get_Player().Get_Info().IncreaseDay();
//			Get_Merchant().Get_Inven()->SetMerchantInven();
//			break;
//
//		case 2:
//			//����
//			if (Get_Player().Get_Info().Get_CurStat()->Get_HP() == 0)
//			{
//				cout << "�޽��� �ʿ�." << endl;
//				system("pause");
//				continue;
//			}
//
//			Select_Dungeon();
//
//			break;
//
//		case 3:
//			//����ǰ
//			system("cls");
//
//			Get_Player().Get_Info().Select_Item(&Get_InputManager(), nullptr);
//
//			break;
//		case 4:
//			//����
//			Open_Shop();
//			break;
//		case 5:
//			//����&����
//			Save_Player();
//			SAFE_DELETE(m_pPlayer);
//			SAFE_DELETE(m_pMerchant);
//			return;
//		case 999:
//			//ġƮ
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

	//�κ��丮 ������, �Ҵ�, ������ ȣ�� ��
	//�� �Լ� �ּ� ����־ ��������.

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "../Data/Save.txt", "rb") == 0)
	{//���� ã�� ����
		size_t iResult(0);
		iResult = fread(&Get_Player(), sizeof(CInfo), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "�ҷ����� ����" << endl;
			system("pause");
		}

		fclose(pLoadFile);

		Get_Player().Get_Info().Get_Inven()->Initialize();
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
//		cout << "������ġ: ������" << endl;
//		cout << "<���� ��� ����>" << endl;
//		LINE_LINE;
//		Set_Color(GREEN);
//		cout << "[1] �ʿ� " << endl; // 2.�� 3.���� 4.����" << endl;
//		Set_Color(GRAY);
//
//		Set_Color(YELLOW);
//		cout << "[2] �� " << endl;
//		Set_Color(GRAY);
//
//		Set_Color(RED);
//		cout << "[3] ���� " << endl;
//		Set_Color(GRAY);
//
//		cout << "[4] ����ó�� ���ư��� " << endl;
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
//		cout << "������ġ: ����" << endl;
//		LINE_LINE;
//		cout << "[1] ����" << endl;
//		cout << "[2] �Ǹ�" << endl;
//		cout << "[3] ����ó�� ���ư���" << endl;
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
//		cout << "������ ǰ���� ��ȣ�� ����(���=0)" << endl;
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
//			cout << "�������� �����մϴ�." << endl;
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
//		cout << "�Ȱ���� ǰ���� ��ȣ�� ����(���=0)" << endl;
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
//	cout << "���� ��ȭ: ";
//	Set_Color(YELLOW);
//	cout << Get_Player().Get_Info().Get_Gold() << "G" << endl;
//	Set_Color(GRAY);
//
//	cout << "�÷��̾��� ";
//	Get_Player().Get_Info().Get_Inven()->PrintAll();
//
//	LINE;
//
//	cout << "������";
//	Get_Merchant().Get_Inven()->PrintAll();
//	cout << endl;
//}

void CMainGame::Save_Player()
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//�� ���� ���� ����

		size_t iResult(0);
		iResult = fwrite(&Get_Player(), sizeof(CInfo), 1, pSaveFile);
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
