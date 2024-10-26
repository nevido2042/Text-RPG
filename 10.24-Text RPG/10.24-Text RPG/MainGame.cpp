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
		cout << "1.�ʿ� 2.�� 3.���� 4.����" << endl;

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

		cout << "1.���� 2.�Ǹ� 3.������" << endl;
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

	SetPrintColor(YELLOW);
	cout << Get_Player().Get_Gold() << "G" << endl;
	SetPrintColor(GRAY);

	cout << "�÷��̾��� ";
	Get_Player().Get_Inven()->PrintAll();

	cout << "===============================" << endl;

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
			SetPrintColor(GREEN);
			cout << "���� ��ġ: �ʿ�" << endl;
			SetPrintColor(GRAY);
			break;
		case Mountain:
			SetPrintColor(YELLOW);
			cout << "���� ��ġ: ��" << endl;
			SetPrintColor(GRAY);
			break;
		case Cave:
			SetPrintColor(RED);
			cout << "���� ��ġ: ����" << endl;
			SetPrintColor(GRAY);
			break;
		}

		cout << "[�ൿ ����]" << endl;
		cout << "1.��� 2.Ž�� 3.����" << endl;
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
			//�� ����, ����(DEX), ����(INT)-�̹�,����,����
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
	CInfo* pEnemy = new CInfo;
	strcpy_s(pEnemy->Get_Name(), NAME_LEN, "???");
	pEnemy->Get_Stat()->SetStatRandom(_iValue);
	pEnemy->ResetStat();

	Render_Battle_Info(pEnemy);

	SetPrintColor(YELLOW);
	cout << "���Ϳ� �����ߴ�." << endl;
	SetPrintColor(GRAY);

	system("pause");

	Start_Battle(pEnemy);

	SAFE_DELETE(pEnemy);

	return;
}

void CMainGame::Render_Battle_Info(CInfo* _pEnemy)
{
	system("cls");
	Get_Player().PrintInfo();
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	_pEnemy->PrintInfo();
}

void CMainGame::Start_Battle(CInfo* _pEnemy)
{
	Render_Battle_Info(_pEnemy);

	if (_pEnemy->Get_CurStat()->Get_DEX() > Get_Player().Get_CurStat()->Get_DEX())
	{
		//_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "������ ��ø�� �� ����." << endl;
		SetPrintColor(YELLOW);
		cout << "������ ���� ����!" << endl;
		SetPrintColor(GRAY);

		cout << endl;
		system("pause");

		Try_Attack(_pEnemy, &Get_Player());
		Render_Battle_Info(_pEnemy);

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Render_Battle_Info(_pEnemy);
			
			Get_Player().Get_CurStat()->Set_HP(0);
			SetPrintColor(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			SetPrintColor(GRAY);

			cout << endl;

			system("pause");

			return;
		}
	}

	while (true)
	{
		Render_Battle_Info(_pEnemy);

		//cout << "���͸� �߰���." << endl;
		cout << "[�ൿ ����]" << endl;
		cout << "1.���� 2.������ 3.���� " << endl;
		if (Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_Input())
		{
		case 1:
		{
			//����
			Try_Attack(&Get_Player(), _pEnemy);

			Render_Battle_Info(_pEnemy);
			cout << endl;

			if (_pEnemy->Get_CurStat()->Get_HP() <= 0)
			{
				_pEnemy->Get_CurStat()->Set_HP(0);

				SetPrintColor(YELLOW);
				cout << "���� ������!" << endl;
				SetPrintColor(GRAY);

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
			if (Select_Item(_pEnemy) == SUCCESS)
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

				SetPrintColor(YELLOW);
				cout << "���� ����" << endl;
				SetPrintColor(GRAY);

				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "MonsterDice: " << iMonsterDice << endl;
			SetPrintColor(YELLOW);
			cout << "���� ����" << endl;
			SetPrintColor(GRAY);

			system("pause");
			break;
		}
		default:
			continue;
		}

		SetPrintColor(YELLOW);
		cout << "���� ��" << endl;
		SetPrintColor(GRAY);
		cout << endl;

		system("pause");

		Render_Battle_Info(_pEnemy);
		Try_Attack(_pEnemy, &Get_Player());

		Render_Battle_Info(_pEnemy);

		if (Get_Player().Get_CurStat()->Get_HP() <= 0)
		{
			Get_Player().Get_CurStat()->Set_HP(0);

			SetPrintColor(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			SetPrintColor(GRAY);

			cout << "���� ����" << endl;
			system("pause");
			return;
		}
	}
}

void CMainGame::Try_Attack(CInfo* _pAttacker, CInfo* _pTarget)
{
	SetPrintColor(YELLOW);
	cout << _pAttacker->Get_Name() << "�� ����" << endl;
	SetPrintColor(GRAY);

	int AttackerDice = Roll_Dice(_pAttacker->Get_CurStat()->Get_DEX());
	int TargetDice = Roll_Dice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
		SetPrintColor(RED);
		cout << _pAttacker->Get_Name() << "�� ���� ����." << endl;
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
			cout << _pAttacker->Get_Name() << "�� ������ �޼ҿ� ����." << endl;
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
		cout << _pAttacker->Get_Name() << "�� ���� ������." << endl;
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

int CMainGame::Select_Item(CInfo* _pEnemy)
{
	Render_Battle_Info(_pEnemy);

	while ((true))
	{
		Render_Battle_Info(_pEnemy);

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
		selectedItem.Use(&Get_Player(), _pEnemy);

		Render_Battle_Info(_pEnemy);

		return SUCCESS;
	}
}

void CMainGame::Trigger_Trap(int _iValue)
{
	system("cls");
	Get_Player().PrintInfo();

	SetPrintColor(YELLOW);
	cout << "����(" << _iValue << ")�� �۵��Ǿ���!" << endl;
	SetPrintColor(GRAY);

	cout << "�ֻ��� ������(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = Roll_Dice(Get_Player().Get_CurStat()->Get_DEX());
	if (iDice_DEX > _iValue)
	{
		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		SetPrintColor(YELLOW);
		cout << "����� ������� ������ ���ߴ�." << endl;
		SetPrintColor(GRAY);

		system("pause");
		return;
	}
	else
	{
		Get_Player().Get_CurStat()->Add_HP(-_iValue);

		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		SetPrintColor(RED);
		cout << "������ ���ظ� �޾Ҵ�." << endl;
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
		cout << "�������� ��� ����(" << _iValue << ")�� �߰��ߴ�._" << endl;
		SetPrintColor(GRAY);

		cout << "1.���� Ǯ��(INT) 2.�����ϱ�" << endl;

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
				SetPrintColor(YELLOW);
				cout << "���ڿ� �ɸ� ������ �����ߴ�." << endl;
				cout << "������ ȹ�� �ߴ�." << endl;
				SetPrintColor(GRAY);

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "����");
				item.Set_Value(500);

				Get_Player().Get_Inven()->AddItem(item);

				system("pause");
			}
			else
			{
				cout << "�ֻ��� ���: " << iDice_INT << endl;
				SetPrintColor(YELLOW);
				cout << "������ �������� ���ߴ�." << endl;
				SetPrintColor(GRAY);

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
