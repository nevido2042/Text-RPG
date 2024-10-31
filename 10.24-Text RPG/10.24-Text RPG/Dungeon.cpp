#include "pch.h"
#include "Dungeon.h"
#include "Player.h"
#include "Merchant.h"

CDungeon::CDungeon() 
	:m_iValue(0), m_pPlayer(nullptr), m_pInputManager(nullptr), m_pEnemy(nullptr)
{
	/*m_iValue = 0;
	m_pPlayer = nullptr;
	m_pInputManager = nullptr;
	m_pEnemy = nullptr;*/
}

CDungeon::CDungeon(CPlayer* _pPlayer, int _iValue, CInputManager* _InputManager)
	:m_pPlayer(_pPlayer), m_iValue(_iValue), m_pInputManager(_InputManager), m_pEnemy(nullptr)
{
	//CDungeon();

	/*m_pPlayer = _pPlayer;
	m_iValue = _iValue;
	m_pInputManager = _InputManager;*/
}

CDungeon::~CDungeon()
{
	SAFE_DELETE(m_pEnemy);
}

CPlayer& CDungeon::Get_Player()
{
	return *m_pPlayer;
}

int CDungeon::Get_Value()
{
	return m_iValue;
}

CInputManager& CDungeon::Get_InputManager()
{
	return *m_pInputManager;
}

CEnemy& CDungeon::Get_Enemy()
{
	return *m_pEnemy;
}

void CDungeon::Set_Enemy(CEnemy* _pEnemy)
{
	if (m_pEnemy != nullptr)
	{
		PRINT_ERROR;
	}

	m_pEnemy = _pEnemy;
	Get_Enemy().Initialize();
}

void CDungeon::Initialize()
{
	while (true)
	{
		if (Get_Player().Get_Info().Get_CurStat()->Get_HP() == 0)
		{
			cout << "ü���� ��� ������ �� �� �����ϴ�." << endl;
			system("pause");
			return;
		}

		system("cls");
		Get_Player().Get_Info().PrintInfo();

		switch (Get_Value())
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

		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
		{
			continue;
		}
		switch (Get_InputManager().Get_Input())
		{
		case 1:
			//���
			//_pPlayer->ResetStat();
			Get_Player().Get_Info().Get_CurStat()->Add_HP(-1);

			break;
		case 2:
			//Ž��
			Get_Player().Get_Info().Get_CurStat()->Add_HP(-1);
			//�� ����, ����(DEX) ������ ���ҽ�Ű�� ȿ��, ����(INT)-�̹�,����,����
			Trigger_Random_Event(Get_Value());
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

void CDungeon::Update()
{
}

void CDungeon::Release()
{
}

void CDungeon::Render_Battle_Info()
{
	system("cls");
	Get_Player().Get_Info().PrintInfo();

	Set_Color(VIOLET);
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	Set_Color(GRAY);

	Get_Enemy().Get_Info().PrintInfo();
}

void CDungeon::Start_Battle()
{
	Render_Battle_Info();

	if (Get_Enemy().Get_Info().Get_CurStat()->Get_DEX() > Get_Player().Get_Info().Get_CurStat()->Get_DEX())
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

		if (Get_Player().Get_Info().Get_CurStat()->Get_HP() <= 0)
		{
			Render_Battle_Info();

			Get_Player().Get_Info().Get_CurStat()->Set_HP(0);
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

		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_InputManager().Get_Input())
		{
		case 1:
		{
			//����
			Get_Player().Try_Attack(&Get_Enemy());

			Render_Battle_Info();
			cout << endl;

			if (Get_Enemy().Get_Info().Get_CurStat()->Get_HP() <= 0)
			{
				Get_Enemy().Get_Info().Get_CurStat()->Set_HP(0);

				Set_Color(YELLOW);
				cout << "���� ������!" << endl;
				Set_Color(GRAY);

				cout << "���� ����" << endl;

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "Test Item");
				item.Set_Value(50);
				cout << "������ ȹ��:" << item.Get_Name() << endl;
				Get_Player().Get_Info().Get_Inven()->AddItem(item);

				system("pause");
				return;
			}

			//system("pause");

			break;
		}

		case 2:
			//������
			if (Get_Player().Select_Item(&Get_InputManager(), &Get_Enemy().Get_Info()) == SUCCESS)
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
			int iPlayerDice = Get_Player().Roll_Dice(Get_Player().Get_Info().Get_CurStat()->Get_DEX());
			int iEnemyDice = Get_Enemy().Roll_Dice(Get_Enemy().Get_Info().Get_CurStat()->Get_DEX());


			if (iPlayerDice > iEnemyDice)
			{
				cout << "PlayerDice: " << iPlayerDice << endl;
				cout << "EnemyDice: " << iEnemyDice << endl;

				Set_Color(YELLOW);
				cout << "���� ����" << endl;
				Set_Color(GRAY);

				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "EnemyDice: " << iEnemyDice << endl;
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

		if (Get_Player().Get_Info().Get_CurStat()->Get_HP() <= 0)
		{
			Get_Player().Get_Info().Get_CurStat()->Set_HP(0);

			Set_Color(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			Set_Color(GRAY);

			cout << "���� ����" << endl;
			system("pause");
			return;
		}
	}
}

void CDungeon::Trigger_Random_Event(int _iValue)
{
	const int iEventCount = 4;
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
	case 4:
		Face_Merchant();
		return;
	default:
		cout << __FUNCTION__ << endl;
		system("pause");
		break;
	}
}

void CDungeon::Face_Enemy(int _iValue)
{
	Set_Enemy(new CEnemy);
	strcpy_s(Get_Enemy().Get_Info().Get_Name(), NAME_LEN, "???");
	Get_Enemy().Get_Info().Get_Stat()->SetStatRandom(_iValue);
	Get_Enemy().Get_Info().ResetStat();

	Render_Battle_Info();

	Set_Color(YELLOW);
	cout << "���Ϳ� �����ߴ�." << endl;
	Set_Color(GRAY);

	system("pause");

	Start_Battle();

	SAFE_DELETE(m_pEnemy);

	return;
}

void CDungeon::Trigger_Trap(int _iValue)
{
	system("cls");
	Get_Player().Get_Info().PrintInfo();

	Set_Color(YELLOW);
	cout << "����(" << _iValue << ")�� �۵��Ǿ���!" << endl;
	Set_Color(GRAY);

	cout << "�ֻ��� ������(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = Get_Player().Roll_Dice(Get_Player().Get_Info().Get_CurStat()->Get_DEX());
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
		Get_Player().Get_Info().Get_CurStat()->Add_HP(-_iValue);

		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		Set_Color(RED);
		cout << "������ ���ظ� �޾Ҵ�." << endl;
		Set_Color(GRAY);

		system("pause");

		system("cls");
		Get_Player().Get_Info().PrintInfo();

		return;
	}
}

void CDungeon::Find_Magic_Box(int _iValue)
{
	while (true)
	{
		system("cls");
		Get_Player().Get_Info().PrintInfo();

		Set_Color(YELLOW);
		cout << "�������� ��� ����(" << _iValue << ")�� �߰��ߴ�._" << endl;
		Set_Color(GRAY);

		LINE_LINE;
		cout << "[1] ���� Ǯ��(INT)" << endl;
		cout << "[2] �����ϱ�" << endl;
		LINE_LINE;

		if (Get_InputManager().Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (Get_InputManager().Get_Input())
		{
		case 1:
			//���� Ǯ��
		{
			int iDice_INT = Get_Player().Roll_Dice(Get_Player().Get_Info().Get_CurStat()->Get_INT());

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

				Get_Player().Get_Info().Get_Inven()->AddItem(item);

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

void CDungeon::Face_Merchant()
{

	Set_Color(YELLOW);
	cout << "������ ������ ������!" << endl;
	Set_Color(GRAY);

	system("pause");

	CMerchant* Merchant = new CMerchant;
	Merchant->Initialize();
	Merchant->Set_Dungeon_Merchant_Inven();

	Merchant->Open_Shop(&Get_Player(), &Get_InputManager());

	SAFE_DELETE(Merchant);
}
