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

		cout << "[���� �޴�]" << endl;
		cout << endl;

		cout << "1.�� ���� 2.�������� 3.�̾��ϱ�" << endl;
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
			//Get_Player().Select_Task(); //�� �Լ��� �÷��̾� ���� ����ϳ�
			Select_Task(); 
		}
		else
		{
			cout << "�÷��̾� ���� ����" << endl;
			system("pause");
		}
	}
}

int CMainGame::Receive_Input()
{
	cout << "�Է�: ";
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
	if (!cin) //�ڷ����� �ٸ� ���� ��� ���� �� üũ
	{
		cin.clear();

		while (cin.get() != '\n');

		//cout << "�߸��� �Է�" << endl;
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
	//���ε� ���߿� ó������
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
		cout << "������ġ: ����ó" << endl;
		cout << "<�ൿ ����>" << endl;
		cout << " 1.�޽� 2.���� 3.����ǰ 4.���� 5.����&���� 999.ġƮ" << endl;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			//�޽�
			Get_Player().ResetStat();
			Get_Player().IncreaseDay();
			pMerchant->Get_Inven()->SetMerchantInven();
			break;

		case 2:
			//����
			if (_pPlayer->Get_CurStat()->Get_HP() == 0)
			{
				cout << "�޽��� �ʿ�." << endl;
				system("pause");
				continue;
			}

			SelectDungeon(_pPlayer);

			break;

		case 3:
			//����ǰ
			system("cls");
			_pPlayer->ResetStat();
			_pPlayer->Get_Inven()->PrintAll();
			system("pause");
			break;
		case 4:
			//����
			OpenShop(_pPlayer, pMerchant);
			break;
		case 5:
			//����&����
			SaveCharacter(_pPlayer);
			SAFE_DELETE(_pPlayer);
			SAFE_DELETE(pMerchant);
			return;
		case 999:
			//ġƮ
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
	{//���� ã�� ����
		size_t iResult(0);
		iResult = fread(&Get_Player(), sizeof(CInfo), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "�ҷ����� ����" << endl;
			system("pause");
		}

		fclose(pLoadFile);
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
		//cout << "====================" << endl;
		cout << "<ĳ���� ����>" << endl;
		cout << endl;

		cout << "�̸�" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> Get_Player().Get_Name(); //������ ���ΰ�? //�׷��� ������� �ι�� �� �ϴ�

		if (strlen(Get_Player().Get_Name()) >= NAME_LEN)
		{
			cout << "�̸� ���� �ʰ�!" << endl;
			//cout << sizeof((*_ppPlayer)->szName) << endl;
			system("pause");
			continue;
		}

		break;
	}
}
