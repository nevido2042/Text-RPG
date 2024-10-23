#include "TextRPG.h"
#include "pch.h"
#include "misc.h"

//#include "inventory.h"
//typedef struct tagInventory INVEN;
//extern void AddItem(ITEM _item);


void CreateCharacter(INFO** _ppPlayer)
{
	while (true)
	{
		system("cls");
		//cout << "====================" << endl;
		cout << "<ĳ���� ����>" << endl;
		cout << endl;
		*_ppPlayer = new INFO;
		cout << "�̸�" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> (*_ppPlayer)->szName; //������ ���ΰ�? //�׷��� ������� �ι�� �� �ϴ�

		if (strlen((*_ppPlayer)->szName) >= NAME_LEN)
		{
			cout << "�̸� ���� �ʰ�!" << endl;
			//cout << sizeof((*_ppPlayer)->szName) << endl;
			system("pause");
			continue;
		}

		break;
	}

	SetSTAT(*_ppPlayer);
}

void SetSTAT(INFO* _pPlayer)
{
	int iInput(0);
	_pPlayer->stat.SetStatRandom();

	while (true)
	{
		system("cls");
		cout << "====================" << endl;
		cout << "<�ɷ�ġ ����>" << endl;
		cout << endl;

		_pPlayer->PrintName();
		_pPlayer->stat.PrintALL();

		cout << "====================" << endl;
		cout << "1.�ֻ��������� 2.����" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			_pPlayer->stat.SetStatRandom();
			continue;
		case 2:
			_pPlayer->ResetStat();
			return;
		default:
			break;
		}
	}
}

void SelectTask(INFO* _pPlayer)
{
	INFO* pMerchant(nullptr);
	pMerchant = new INFO;
	pMerchant->inven.SetMerchantInven();

	int iInput(0);

	while (true)
	{
		system("cls");
		_pPlayer->PrintInfo();

		SetPrintColor(YELLOW);
		cout << _pPlayer->iGold << 'G' << endl;
		SetPrintColor(GRAY);

		cout << "Day-" << _pPlayer->iDay << endl;
		cout << "������ġ: ����ó" << endl;
		cout << "<�ൿ ����>" << endl;
		cout << " 1.�޽� 2.���� 3.����ǰ 4.���� 5.����&����" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//�޽�
			_pPlayer->ResetStat();
			_pPlayer->iDay++;
			pMerchant->inven.SetMerchantInven();
			break;

		case 2:
			//����
			if (_pPlayer->curStat.iHP == 0)
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
			_pPlayer->inven.PrintAll();
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
		default:
			break;
		}
	}
}

int GetInput(int* _pInput)
{
	cout << "�Է�: ";
	cin >> *_pInput;

	int iTemp = InputCheck();
	if (iTemp == INPUT_ERROR)
	{
		return INPUT_ERROR;
	}

	return SUCCESS;
}

void OpenShop(INFO* _pPlayer, INFO* _pMerchant)
{
	int iInput(0);

	//INFO* merchant = new INFO; //���� �Ϸ翡 �ѹ��� ���µǵ��� �ٲ����

	while (true)
	{
		RenderShop(_pPlayer, _pMerchant);

		cout << "1.���� 2.�Ǹ� 3.������" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			BuyItem(_pPlayer, _pMerchant);
			break;
		case 2:
			SellItem(_pPlayer, _pMerchant);
			break;
		case 3:
			//SAFE_DELETE(merchant);
			return;
		default:
			break;
		}
	}
}

void RenderShop(INFO* _pPlayer, INFO* _pMerchant)
{
	system("cls");

	SetPrintColor(YELLOW);
	cout << _pPlayer->iGold<<"G" << endl;
	SetPrintColor(GRAY);

	cout << "�÷��̾��� ";
	_pPlayer->inven.PrintAll();

	cout << "===============================" << endl;

	cout << "������";
	_pMerchant->inven.PrintAll();

	cout << endl;
}

void BuyItem(INFO* _pPlayer, INFO* _pMerchant)
{
	int iInput(0);
	while (true)
	{
		RenderShop(_pPlayer, _pMerchant);

		cout << "������ ǰ���� ��ȣ�� ����(���=0)" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}
		
		if (iInput == 0)
		{
			break;
		}

		ITEM item = _pMerchant->inven.itemArray[iInput - 1];

		int iItemValue = _pMerchant->inven.itemArray[iInput - 1].iValue;
		if (_pPlayer->iGold >= iItemValue)
		{
			_pPlayer->iGold -= iItemValue;
		}
		else
		{
			cout << "�������� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		if (_pMerchant->inven.RemoveItem(iInput - 1) == SUCCESS)
		{
			_pPlayer->inven.AddItem(item);
		}
	}
}

void SellItem(INFO* _pPlayer, INFO* _pMerchant)
{
	int iInput(0);
	while (true)
	{
		RenderShop(_pPlayer, _pMerchant);

		cout << "�Ȱ���� ǰ���� ��ȣ�� ����(���=0)" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		if (iInput == 0)
		{
			break;
		}

		ITEM item = _pPlayer->inven.itemArray[iInput - 1];
		if (_pPlayer->inven.RemoveItem(iInput - 1) == SUCCESS)
		{
			_pPlayer->iGold += item.iValue;
			_pMerchant->inven.AddItem(item);
		}
	}
}

void SelectDungeon(INFO* _pPlayer)
{
	int iInput(0);
	while (true)
	{
		if (_pPlayer->curStat.iHP == 0)
		{
			return;
		}

		system("cls");
		_pPlayer->PrintInfo();
		cout << "������ġ: ������" << endl;
		cout << "<���� ��� ����>" << endl;
		cout << "1.�ʿ� 2.�� 3.���� 4.����" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//Enter_Grassland(_pPlayer);
			Enter_Dungeon(_pPlayer, Grassland);
			break;
		case 2:
			//Enter_Mountain(_pPlayer);
			Enter_Dungeon(_pPlayer, Mountain);
			break;
		case 3:
			//Enter_Cave(_pPlayer);
			Enter_Dungeon(_pPlayer, Cave);
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

int InputCheck()
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

int RollDice(int iValue)
{
	if (iValue == 0)
		return 0;

	return rand() % iValue + 1;
}

void Enter_Dungeon(INFO* _pPlayer, int _iValue)
{
	int iInput(0);
	while (true)
	{
		if (_pPlayer->curStat.iHP == 0)
		{
			//cout << "�÷��̾� ������" << endl;
			//system("pause");
			return;
		}

		system("cls");
		_pPlayer->PrintInfo();

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
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}
		switch (iInput)
		{
		case 1:
			//���
			//_pPlayer->ResetStat();
			_pPlayer->curStat.iHP -= 1;

			break;
		case 2:
			//Ž��
			//�� ����, ����(DEX), ����(INT)-�̹�,����,����
			TriggerRandomEvent(_pPlayer, _iValue);
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

//void Enter_Grassland(INFO* _pPlayer)
//{
//	int iInput(0);
//	while (true)
//	{
//		if (_pPlayer->curStat.iHP == 0)
//		{
//			return;
//		}
//
//		system("cls");
//		_pPlayer->PrintInfo();
//
//		SetPrintColor(GREEN);
//		cout << "���� ��ġ: �ʿ�" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[�ൿ ����]" << endl;
//		cout << "1.��� 2.Ž�� 3.����" << endl;
//		if (GetInput(&iInput) == INPUT_ERROR)
//		{
//			continue;
//		}
//		switch (iInput)
//		{
//		case 1:
//			_pPlayer->curStat.iHP -= 1;
//			//_pPlayer->ResetStat();
//			break;
//		case 2:
//			FaceMonster(_pPlayer, 1);
//			break;
//		case 3:
//			return;
//		default:
//			break;
//		}
//	}
//}
//
//void Enter_Mountain(INFO* _pPlayer)
//{
//	int iInput(0);
//	while (true)
//	{
//		if (_pPlayer->curStat.iHP == 0)
//		{
//			//cout << "�÷��̾� ������" << endl;
//			//system("pause");
//			return;
//		}
//
//		system("cls");
//		_pPlayer->PrintInfo();
//
//		SetPrintColor(YELLOW);
//		cout << "���� ��ġ: ��" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[�ൿ ����]" << endl;
//		cout << "1.��� 2.Ž�� 3.����" << endl;
//		if (GetInput(&iInput) == INPUT_ERROR)
//		{
//			continue;
//		}
//		switch (iInput)
//		{
//		case 1:
//			//���
//			//_pPlayer->ResetStat();
//			_pPlayer->curStat.iHP -= 1;
//
//			break;
//		case 2:
//			//Ž��
//			//�� ����, ����(DEX), ����(INT)-�̹�,����,����
//			TriggerRandomEvent(_pPlayer, 2);
//			//FaceMonster(_pPlayer, 2);
//			break;
//		case 3:
//			//����
//			return;
//		default:
//			break;
//		}
//	}
//}
//
//void Enter_Cave(INFO* _pPlayer)
//{
//	int iInput(0);
//	while (true)
//	{
//		if (_pPlayer->curStat.iHP == 0)
//		{
//			return;
//		}
//
//		system("cls");
//		_pPlayer->PrintInfo();
//
//		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
//		SetPrintColor(RED);
//		cout << "���� ��ġ: ����" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[�ൿ ����]" << endl;
//		cout << "1.��� 2.Ž�� 3.����" << endl;
//		if (GetInput(&iInput) == INPUT_ERROR)
//		{
//			continue;
//		}
//		switch (iInput)
//		{
//		case 1:
//			//_pPlayer->ResetStat();
//			_pPlayer->curStat.iHP -= 1;
//
//			break;
//		case 2:
//			FaceMonster(_pPlayer, 3);
//			break;
//		case 3:
//			return;
//		default:
//			break;
//		}
//	}
//}

void TriggerRandomEvent(INFO* _pPlayer, int _iValue)
{
	const int iEventCount = 3; 
	int iRandNum = rand() % iEventCount + 1;

	switch (iRandNum)
	{
	case 1:
		FaceMonster(_pPlayer, _iValue);
		return;
	case 2:
		TriggerTrap(_pPlayer, _iValue);
		return;
	case 3:
		FindMagicBox(_pPlayer, _iValue);
		return;
	default:
		cout << __FUNCTION__ << endl;
		system("pause");
		break;
	}
}

void TriggerTrap(INFO* _pPlayer, int _iValue)
{
	system("cls");
	_pPlayer->PrintInfo();

	cout << "����(" << _iValue << ")�� �۵��Ǿ���!" << endl;
	cout << "�ֻ��� ������(DEX)" << endl;
	system("pause");

	int iDice_DEX = RollDice(_pPlayer->curStat.iDEX);
	if (iDice_DEX > _iValue)
	{
		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		cout << "����� ������� ������ ���ߴ�." << endl;
		system("pause");
		return;
	}
	else
	{
		_pPlayer->curStat.iHP -= _iValue;

		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		cout << "������ ���ظ� �޾Ҵ�." << endl;
		system("pause");

		system("cls");
		_pPlayer->PrintInfo();

		return;
	}
}

void FindMagicBox(INFO* _pPlayer, int _iValue)
{
	int iInput(0);

	while (true)
	{
		system("cls");
		_pPlayer->PrintInfo();

		cout << "�������� ��� ����(" << _iValue << ")�� �߰��ߴ�._" << endl;
		cout << "1.���� Ǯ��(INT) 2.�����ϱ�" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//���� Ǯ��
		{
			int iDice_INT = RollDice(_pPlayer->curStat.iINT);

			if (iDice_INT > _iValue)
			{
				cout << "�ֻ��� ���: " << iDice_INT << endl;
				cout << "���ڿ� �ɸ� ������ �����ߴ�." << endl;
				cout << "������ ȹ�� �ߴ�." << endl;

				ITEM item;
				strcpy_s(item.szName, "����");
				item.iValue = 500;
				
				_pPlayer->inven.AddItem(item);

				system("pause");
			}
			else
			{
				cout << "�ֻ��� ���: " << iDice_INT << endl;
				cout << "������ �������� ���ߴ�." << endl;
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

void FaceMonster(INFO* _pPlayer, int _iValue)
{
	INFO* pMonster = new INFO;
	strcpy_s(pMonster->szName, "???");
	pMonster->stat.SetStatRandom(_iValue);
	pMonster->ResetStat();

	RenderBattleInfo(_pPlayer, pMonster);

	cout << "���Ϳ� �����ߴ�." << endl;

	system("pause");

	StartBattle(_pPlayer, pMonster);

	SAFE_DELETE(pMonster);

	return;
}

void StartBattle(INFO* _pPlayer, INFO* _pMonster)
{
	int iInput(0);
	RenderBattleInfo(_pPlayer, _pMonster);

	if (_pMonster->curStat.iDEX > _pPlayer->curStat.iDEX)
	{
		//_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "������ ��ø�� �� ����." << endl;
		cout << "������ ���� ����!" << endl;
		cout << endl;
		system("pause");

		TryAttack(_pMonster, _pPlayer);
		RenderBattleInfo(_pPlayer, _pMonster);
		
		if (_pPlayer->curStat.iHP <= 0)
		{
			RenderBattleInfo(_pPlayer, _pMonster);

			_pPlayer->curStat.iHP = 0;
			cout << "�÷��̾� ������!" << endl;
			cout << endl;

			system("pause");

			return;
		}
	}

	while (true)
	{
		RenderBattleInfo(_pPlayer, _pMonster);

		//cout << "���͸� �߰���." << endl;
		cout << "[�ൿ ����]" << endl;
		cout << "1.���� 2.������ 3.���� " << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
		{
			//����
			TryAttack(_pPlayer, _pMonster);

			RenderBattleInfo(_pPlayer, _pMonster);
			cout << endl;

			if (_pMonster->curStat.iHP <= 0)
			{
				_pMonster->curStat.iHP = 0;

				cout << "���� ������!" << endl;
				cout << "���� ����" << endl;

				ITEM item;
				strcpy_s(item.szName, "Test Item");
				item.iValue = 50;
				cout << "������ ȹ��:" << item.szName << endl;
				_pPlayer->inven.AddItem(item);

				system("pause");
				return;
			}

			system("pause");

			break;
		}
			
		case 2:
			//������
			if (SelectItem(_pPlayer, _pMonster) == SUCCESS)
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
			int iPlayerDice = RollDice(_pPlayer->curStat.iDEX);
			int iMonsterDice = RollDice(_pMonster->curStat.iDEX);

			if (iPlayerDice > iMonsterDice)
			{
				cout << "PlayerDice: " << iPlayerDice << endl;
				cout << "MonsterDice: " << iMonsterDice << endl;

				cout << "���� ����" << endl;
				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "MonsterDice: " << iMonsterDice << endl;

			cout << "���� ����" << endl;
			system("pause");
			break;
		}
		default:
			continue;
		}

		RenderBattleInfo(_pPlayer, _pMonster);

		TryAttack(_pMonster, _pPlayer);

		RenderBattleInfo(_pPlayer, _pMonster);

		if (_pPlayer->curStat.iHP <= 0)
		{
			_pPlayer->curStat.iHP = 0;

			cout << "�÷��̾� ������!" << endl;
			cout << "���� ����" << endl;
			system("pause");
			return;
		}
	}

}

void RenderBattleInfo(INFO* _pPlayer, INFO* _pMonster)
{
	system("cls");
	_pPlayer->PrintInfo();
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	_pMonster->PrintInfo();
}

void TryAttack(INFO* _pAttacker, INFO* _pTarget)
{
	cout << _pAttacker->szName << "�� ����" << endl;

	int AttackerDice = RollDice(_pAttacker->curStat.iDEX);
	int TargetDice = RollDice(_pTarget->curStat.iDEX);

	if (AttackerDice > TargetDice)
	{
		cout << _pAttacker->szName << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->szName << " Dice_DEX: " << TargetDice << endl;

		_pTarget->curStat.iHP -= _pAttacker->curStat.iSTR;
		cout << _pAttacker->szName << "�� ���� ����." << endl;
		cout << endl;

		int AttackerDice_LUK = RollDice(_pAttacker->curStat.iLUK);
		int TargetDice_LUK = RollDice(_pTarget->curStat.iLUK);

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << _pAttacker->szName << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->szName << " Dice_LUK: " << TargetDice_LUK << endl;

			_pTarget->curStat.iHP -= _pAttacker->curStat.iSTR;
			cout << _pAttacker->szName << "�� ������ �޼ҿ� ����." << endl;
			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << _pAttacker->szName << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->szName << " Dice_DEX: " << TargetDice << endl;

		cout << _pAttacker->szName << "�� ���� ������." << endl;
		cout << endl;
		system("pause");
	}
}
 
int SelectItem(INFO* _pPlayer, INFO* _pMonster)
{
	RenderBattleInfo(_pPlayer, _pMonster);

	int iInput(0);

	while ((true))
	{
		RenderBattleInfo(_pPlayer, _pMonster);
		
		_pPlayer->inven.PrintAll();
		cout << "����� ������ ����(���=0): ";
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		if (iInput == 0)
		{
			return _ERROR;
		}

		_pPlayer->inven.itemArray[iInput - 1].Use(_pPlayer, _pMonster);
		system("pause");
		return SUCCESS;
	}

}

void LoadCharacter(INFO** _pPlayer)
{
	*_pPlayer = new INFO;

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "../Data/Save.txt", "rb") == 0)
	{//���� ã�� ����
		size_t iResult(0);
		iResult = fread(*_pPlayer, sizeof(INFO), 1, pLoadFile);
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

void SaveCharacter(INFO* _pPlayer)
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//�� ���� ���� ����

		size_t iResult(0);
		iResult = fwrite(_pPlayer, sizeof(INFO), 1, pSaveFile);
		if (iResult != 1)//fwirte�� ī��Ʈ�� ��ȯ �ϴ±���
		{
			cout << "iResult: " << iResult << endl;
			//cout << "INFO: " << sizeof(INFO) << endl;

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

void Run_TextRPG()
{
	srand(unsigned(time(NULL)));

	INFO* pPlayer(nullptr);
	int iInput(0);

	while (true)
	{
		system("cls");
		cout << "<TEXT RPG>" << endl;
		cout << endl;

		cout << "[���� �޴�]" << endl;
		cout << endl;

		cout << "1.�� ���� 2.�������� 3.�̾��ϱ�" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			CreateCharacter(&pPlayer);
			SelectTask(pPlayer);
			break;
		case 2:
			//SAFE_DELETE(pPlayer);
			return;

		case 3:
			LoadCharacter(&pPlayer);
			SelectTask(pPlayer);
			break;

		default:
			cout << "default";
			break;
		}
	}
}