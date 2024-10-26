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
	return *m_pEnemy;
}

void CMainGame::Set_Enemy(CInfo* _pEnemy)
{
	m_pEnemy = _pEnemy;
}

CMainGame::CMainGame()
{
	srand(unsigned(time(NULL)));

	m_iInput = 0;

	m_pPlayer = nullptr;

	m_pMerchant = nullptr;

	m_pEnemy = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
}

void CMainGame::Update()
{
}

void CMainGame::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMerchant);
	SAFE_DELETE(m_pEnemy);
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
	Set_Random_STAT();
}

void CMainGame::Select_Task()
{
	//���ε� ���߿� ó������
	Set_Merchant(new CInfo);
	Get_Merchant().Get_Inven()->SetMerchantInven();

	while (true)
	{
		system("cls");
		Get_Player().PrintInfo();

		Set_Color(YELLOW);
		cout << Get_Player().Get_Gold() << 'G' << endl;
		Set_Color(GRAY);

		cout << "Day - " << Get_Player().Get_Day() << endl;
		cout << "������ġ: ����ó" << endl;
		LINE_LINE;
		cout << " [1] �޽�" << endl;
		cout << " [2] ����" << endl;
		cout << " [3] ����ǰ" << endl;
		cout << " [4] ����" << endl;
		cout << " [5] ���� & ����" << endl;
		cout << " [999] ġƮ" << endl;
		LINE_LINE;


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
			Get_Merchant().Get_Inven()->SetMerchantInven();
			break;

		case 2:
			//����
			if (Get_Player().Get_CurStat()->Get_HP() == 0)
			{
				cout << "�޽��� �ʿ�." << endl;
				system("pause");
				continue;
			}

			Select_Dungeon();

			break;

		case 3:
			//����ǰ
			system("cls");
			Get_Player().ResetStat();
			Get_Player().Get_Inven()->PrintAll();
			system("pause");
			break;
		case 4:
			//����
			Open_Shop();
			break;
		case 5:
			//����&����
			Save_Player();
			SAFE_DELETE(m_pPlayer);
			SAFE_DELETE(m_pMerchant);
			return;
		case 999:
			//ġƮ
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
		cout << "<ĳ���� ����>" << endl;
		LINE_LINE;

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

void CMainGame::Set_Random_STAT()
{
	Get_Player().Get_Stat()->SetStatRandom();

	while (true)
	{
		system("cls");
		cout << "<�ɷ�ġ ����>" << endl;

		Get_Player().PrintName();
		Get_Player().Get_Stat()->PrintALL();

		LINE_LINE;

		cout << "[1] �ֻ��� ������" << endl;
		cout << "[2] ����" << endl;
		LINE_LINE;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			Get_Player().Get_Stat()->SetStatRandom();
			continue;
		case 2:
			Get_Player().ResetStat();
			return;
		default:
			break;
		}
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
		cout << "������ġ: ������" << endl;
		cout << "<���� ��� ����>" << endl;
		LINE_LINE;
		Set_Color(GREEN);
		cout << "[1] �ʿ� " << endl; // 2.�� 3.���� 4.����" << endl;
		Set_Color(GRAY);

		Set_Color(YELLOW);
		cout << "[2] �� " << endl;
		Set_Color(GRAY);

		Set_Color(RED);
		cout << "[3] ���� " << endl;
		Set_Color(GRAY);

		cout << "[4] ����ó�� ���ư��� " << endl;
		LINE_LINE;

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

		cout << "������ġ: ����" << endl;
		LINE_LINE;
		cout << "[1] ����" << endl;
		cout << "[2] �Ǹ�" << endl;
		cout << "[3] ����ó�� ���ư���" << endl;
		LINE_LINE;


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

		cout << "������ ǰ���� ��ȣ�� ����(���=0)" << endl;
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
			cout << "�������� �����մϴ�." << endl;
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

		cout << "�Ȱ���� ǰ���� ��ȣ�� ����(���=0)" << endl;
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

	cout << "���� ��ȭ: ";
	Set_Color(YELLOW);
	cout << Get_Player().Get_Gold() << "G" << endl;
	Set_Color(GRAY);

	cout << "�÷��̾��� ";
	Get_Player().Get_Inven()->PrintAll();

	LINE;

	cout << "������";
	Get_Merchant().Get_Inven()->PrintAll();
	cout << endl;
}

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

void CMainGame::Enter_Dungeon(int _iValue)
{
	while (true)
	{
		if (Get_Player().Get_CurStat()->Get_HP() == 0)
		{
			//cout << "�÷��̾� ������" << endl;
			//system("pause");
			return;
		}

		system("cls");
		Get_Player().PrintInfo();

		switch (_iValue)
		{
		case Grassland:
			Set_Color(GREEN);
			cout << "���� ��ġ: �ʿ�" << endl;
			Set_Color(GRAY);
			break;
		case Mountain:
			Set_Color(YELLOW);
			cout << "���� ��ġ: ��" << endl;
			Set_Color(GRAY);
			break;
		case Cave:
			Set_Color(RED);
			cout << "���� ��ġ: ����" << endl;
			Set_Color(GRAY);
			break;
		}

		LINE_LINE;
		cout << "[1] ���" << endl;
		cout << "[2] Ž��" << endl;
		cout << "[3] ������� ���ư���" << endl;
		LINE_LINE;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}
		switch (Get_Input())
		{
		case 1:
			//���
			//_pPlayer->ResetStat();
			Get_Player().Get_CurStat()->Add_HP(-1);

			break;
		case 2:
			//Ž��
			Get_Player().Get_CurStat()->Add_HP(-1);
			//�� ����, ����(DEX) ������ ���ҽ�Ű�� ȿ��, ����(INT)-�̹�,����,����
			Trigger_Random_Event(_iValue);
			//FaceMonster(_pPlayer, 2);
			break;
		case 3:
			//����
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

	Set_Color(YELLOW);
	cout << "���Ϳ� �����ߴ�." << endl;
	Set_Color(GRAY);

	system("pause");

	Start_Battle();

	SAFE_DELETE(m_pEnemy);

	return;
}

void CMainGame::Render_Battle_Info()
{
	system("cls");
	Get_Player().PrintInfo();

	Set_Color(VIOLET);
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	Set_Color(GRAY);

	Get_Enemy().PrintInfo();
}

void CMainGame::Start_Battle()
{
	Render_Battle_Info();

	if (Get_Enemy().Get_CurStat()->Get_DEX() > Get_Player().Get_CurStat()->Get_DEX())
	{
		//_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "������ ��ø�� �� ����." << endl;
		Set_Color(YELLOW);
		cout << "������ ���� ����!" << endl;
		Set_Color(GRAY);

		cout << endl;
		system("pause");

		//Try_Attack(&Get_Enemy(), &Get_Player());
		Get_Enemy().Try_Attack(&Get_Player());

		Render_Battle_Info();

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Render_Battle_Info();
			
			Get_Player().Get_CurStat()->Set_HP(0);
			Set_Color(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			Set_Color(GRAY);

			cout << endl;

			system("pause");

			return;
		}
	}

	while (true)
	{
		Render_Battle_Info();

		//cout << "���͸� �߰���." << endl;
		LINE_LINE;
		cout << "[1] ����" << endl;
		cout << "[2] ������" << endl;
		cout << "[3] ����" << endl;
		LINE_LINE;
		
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
		{
			//����
			Get_Player().Try_Attack(&Get_Enemy());

			Render_Battle_Info();
			cout << endl;

			if (Get_Enemy().Get_CurStat()->Get_HP() <= 0)
			{
				Get_Enemy().Get_CurStat()->Set_HP(0);

				Set_Color(YELLOW);
				cout << "���� ������!" << endl;
				Set_Color(GRAY);

				cout << "���� ����" << endl;

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "Test Item");
				item.Set_Value(50);
				cout << "������ ȹ��:" << item.Get_Name() << endl;
				Get_Player().Get_Inven()->AddItem(item);

				system("pause");
				return;
			}

			//system("pause");

			break;
		}

		case 2:
			//������
			if (Select_Item() == SUCCESS)
			{
				break;
			}
			else
			{
				continue;
			}
		case 3:
			//����
		{
			int iPlayerDice = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());
			int iMonsterDice = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());

			if (iPlayerDice > iMonsterDice)
			{
				cout << "PlayerDice: " << iPlayerDice << endl;
				cout << "MonsterDice: " << iMonsterDice << endl;

				Set_Color(YELLOW);
				cout << "���� ����" << endl;
				Set_Color(GRAY);

				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "MonsterDice: " << iMonsterDice << endl;
			Set_Color(YELLOW);
			cout << "���� ����" << endl;
			Set_Color(GRAY);

			system("pause");
			break;
		}
		default:
			continue;
		}

		Set_Color(YELLOW);
		cout << "���� ��" << endl;
		Set_Color(GRAY);
		cout << endl;

		system("pause");

		Render_Battle_Info();
		
		Get_Enemy().Try_Attack(&Get_Player());

		Render_Battle_Info();

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Get_Player().Get_CurStat()->Set_HP(0);

			Set_Color(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			Set_Color(GRAY);

			cout << "���� ����" << endl;
			system("pause");
			return;
		}
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
		cout << "����� ������ ����(���=0): ";
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		if (Get_Input() == 0)
		{
			return _ERROR;
		}

		//������ ��� �����۰�
		//�ҷ������ ���� ��������
		//�Լ� ������ ���� �޶� ������.
		// 
		//�ҷ� ���� �Ҷ� �ٽ� ��ƾ��ϳ�?
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

	Set_Color(YELLOW);
	cout << "����(" << _iValue << ")�� �۵��Ǿ���!" << endl;
	Set_Color(GRAY);

	cout << "�ֻ��� ������(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());
	if (iDice_DEX > _iValue)
	{
		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		Set_Color(YELLOW);
		cout << "����� ������� ������ ���ߴ�." << endl;
		Set_Color(GRAY);

		system("pause");
		return;
	}
	else
	{
		Get_Player().Get_CurStat()->Add_HP(-_iValue);

		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		Set_Color(RED);
		cout << "������ ���ظ� �޾Ҵ�." << endl;
		Set_Color(GRAY);

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

		Set_Color(YELLOW);
		cout << "�������� ��� ����(" << _iValue << ")�� �߰��ߴ�._" << endl;
		Set_Color(GRAY);

		LINE_LINE;
		cout << "[1] ���� Ǯ��(INT)" << endl; 
		cout << "[2] �����ϱ�" << endl;
		LINE_LINE;

		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
			//���� Ǯ��
		{
			int iDice_INT = Roll_Dice(Get_Player().Get_CurStat()->Get_INT());

			if (iDice_INT > _iValue)
			{
				cout << "�ֻ��� ���: " << iDice_INT << endl;
				Set_Color(YELLOW);
				cout << "���ڿ� �ɸ� ������ �����ߴ�." << endl;
				cout << "������ ȹ�� �ߴ�." << endl;
				Set_Color(GRAY);

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "����");
				item.Set_Value(500);

				Get_Player().Get_Inven()->AddItem(item);

				system("pause");
			}
			else
			{
				cout << "�ֻ��� ���: " << iDice_INT << endl;
				Set_Color(YELLOW);
				cout << "������ �������� ���ߴ�." << endl;
				Set_Color(GRAY);

				system("pause");
			}
			return;
		}
		case 2:
			//���� �ϱ�
			return;
		default:
			break;
		}
	}
}
