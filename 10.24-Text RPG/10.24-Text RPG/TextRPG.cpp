#include "pch.h"
#include "TextRPG.h"
#include "misc.h"

void CreateCharacter(CInfo** _ppPlayer)
{
	while (true)
	{
		system("cls");
		LINE_LINE;
		cout << "<ĳ���� ����>" << endl;
		cout << endl;
		*_ppPlayer = new CInfo;
		cout << "�̸�" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> (*_ppPlayer)->Get_Name(); //������ ���ΰ�? //�׷��� ������� �ι�� �� �ϴ�

		if (strlen((*_ppPlayer)->Get_Name()) >= NAME_LEN)
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

void SetSTAT(CInfo* _pPlayer)
{
	int iInput(0);
	_pPlayer->Get_Stat()->SetStatRandom();

	while (true)
	{
		system("cls");
		LINE_LINE;
		cout << "<�ɷ�ġ ����>" << endl;
		cout << endl;

		_pPlayer->PrintName();
		_pPlayer->Get_Stat()->PrintALL();

		LINE_LINE;
		cout << "1.�ֻ��������� 2.����" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			_pPlayer->Get_Stat()->SetStatRandom();
			continue;
		case 2:
			_pPlayer->ResetStat();
			return;
		default:
			break;
		}
	}
}

void SelectTask(CInfo* _pPlayer)
{
	CInfo* pMerchant(nullptr);
	pMerchant = new CInfo;
	pMerchant->Get_Inven()->SetMerchantInven();

	int iInput(0);

	while (true)
	{
		system("cls");
		_pPlayer->PrintInfo();

		Set_Color(YELLOW);
		cout << _pPlayer->Get_Gold() << 'G' << endl;
		Set_Color(GRAY);

		cout << "Day -" << _pPlayer->Get_Day() << endl;
		cout << "������ġ: ����ó" << endl;
		cout << "<�ൿ ����>" << endl;
		cout << " 1.�޽� 2.���� 3.����ǰ 4.���� 5.����&���� 999.ġƮ" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//�޽�
			_pPlayer->ResetStat();
			_pPlayer->IncreaseDay();
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

void OpenShop(CInfo* _pPlayer, CInfo* _pMerchant)
{
	int iInput(0);

	//CInfo* merchant = new CInfo; //���� �Ϸ翡 �ѹ��� ���µǵ��� �ٲ����

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

void RenderShop(CInfo* _pPlayer, CInfo* _pMerchant)
{
	system("cls");

	Set_Color(YELLOW);
	cout << _pPlayer->Get_Gold()<<"G" << endl;
	Set_Color(GRAY);

	cout << "�÷��̾��� ";
	_pPlayer->Get_Inven()->PrintAll();

	LINE_LINE;

	cout << "������";
	_pMerchant->Get_Inven()->PrintAll();

	cout << endl;
}

void BuyItem(CInfo* _pPlayer, CInfo* _pMerchant)
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

		CItem item = _pMerchant->Get_Inven()->Get_ItemArray()[iInput - 1];

		int iItemValue = _pMerchant->Get_Inven()->Get_ItemArray()[iInput - 1].Get_Value();
		if (_pPlayer->Get_Gold() >= iItemValue)
		{
			_pPlayer->AddGold(-iItemValue);
		}
		else
		{
			cout << "�������� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		if (_pMerchant->Get_Inven()->RemoveItem(iInput - 1) == SUCCESS)
		{
			_pPlayer->Get_Inven()->AddItem(item);
		}
	}
}

void SellItem(CInfo* _pPlayer, CInfo* _pMerchant)
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

		CItem item = _pPlayer->Get_Inven()->Get_ItemArray()[iInput - 1];
		if (_pPlayer->Get_Inven()->RemoveItem(iInput - 1) == SUCCESS)
		{
			_pPlayer->AddGold(item.Get_Value());
			_pMerchant->Get_Inven()->AddItem(item);
		}
	}
}

void SelectDungeon(CInfo* _pPlayer)
{
	int iInput(0);
	while (true)
	{
		if (_pPlayer->Get_CurStat()->Get_HP() == 0)
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

void Enter_Dungeon(CInfo* _pPlayer, int _iValue)
{
	int iInput(0);
	while (true)
	{
		if (_pPlayer->Get_CurStat()->Get_HP() == 0)
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
			_pPlayer->Get_CurStat()->Add_HP(-1);

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

//void Enter_Grassland(CInfo* _pPlayer)
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
//void Enter_Mountain(CInfo* _pPlayer)
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
//void Enter_Cave(CInfo* _pPlayer)
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

void TriggerRandomEvent(CInfo* _pPlayer, int _iValue)
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

void TriggerTrap(CInfo* _pPlayer, int _iValue)
{
	system("cls");
	_pPlayer->PrintInfo();

	Set_Color(YELLOW);
	cout << "����(" << _iValue << ")�� �۵��Ǿ���!" << endl;
	Set_Color(GRAY);

	cout << "�ֻ��� ������(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = RollDice(_pPlayer->Get_CurStat()->Get_DEX());
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
		_pPlayer->Get_CurStat()->Add_HP(-_iValue);

		cout << "�ֻ��� ���: " << iDice_DEX << endl;
		Set_Color(RED);
		cout << "������ ���ظ� �޾Ҵ�." << endl;
		Set_Color(GRAY);

		system("pause");

		system("cls");
		_pPlayer->PrintInfo();

		return;
	}
}

void FindMagicBox(CInfo* _pPlayer, int _iValue)
{
	int iInput(0);

	while (true)
	{
		system("cls");
		_pPlayer->PrintInfo();

		Set_Color(YELLOW);
		cout << "�������� ��� ����(" << _iValue << ")�� �߰��ߴ�._" << endl;
		Set_Color(GRAY);

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
			int iDice_INT = RollDice(_pPlayer->Get_CurStat()->Get_INT());

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
				
				_pPlayer->Get_Inven()->AddItem(item);

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

void FaceMonster(CInfo* _pPlayer, int _iValue)
{
	CInfo* pMonster = new CInfo;
	strcpy_s(pMonster->Get_Name(), NAME_LEN, "???");
	pMonster->Get_Stat()->SetStatRandom(_iValue);
	pMonster->ResetStat();

	RenderBattleInfo(_pPlayer, pMonster);

	Set_Color(YELLOW);
	cout << "���Ϳ� �����ߴ�." << endl;
	Set_Color(GRAY);

	system("pause");

	StartBattle(_pPlayer, pMonster);

	SAFE_DELETE(pMonster);

	return;
}

void StartBattle(CInfo* _pPlayer, CInfo* _pMonster)
{
	int iInput(0);
	RenderBattleInfo(_pPlayer, _pMonster);

	if (_pMonster->Get_CurStat()->Get_DEX() > _pPlayer->Get_CurStat()->Get_DEX())
	{
		//_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "������ ��ø�� �� ����." << endl;
		Set_Color(YELLOW);
		cout << "������ ���� ����!" << endl;
		Set_Color(GRAY);

		cout << endl;
		system("pause");

		TryAttack(_pMonster, _pPlayer);
		RenderBattleInfo(_pPlayer, _pMonster);
		
		if (_pPlayer->Get_CurStat()->Get_HP() <= 0)
		{
			RenderBattleInfo(_pPlayer, _pMonster);

			_pPlayer->Get_CurStat()->Set_HP(0);
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

			if (_pMonster->Get_CurStat()->Get_HP() <= 0)
			{
				_pMonster->Get_CurStat()->Set_HP(0);

				Set_Color(YELLOW);
				cout << "���� ������!" << endl;
				Set_Color(GRAY);

				cout << "���� ����" << endl;

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "Test Item");
				item.Set_Value(50);
				cout << "������ ȹ��:" << item.Get_Name() << endl;
				_pPlayer->Get_Inven()->AddItem(item);

				system("pause");
				return;
			}

			//system("pause");

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
			int iPlayerDice = RollDice(_pPlayer->Get_CurStat()->Get_DEX());
			int iMonsterDice = RollDice(_pMonster->Get_CurStat()->Get_DEX());

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
		
		RenderBattleInfo(_pPlayer, _pMonster);

		TryAttack(_pMonster, _pPlayer);

		RenderBattleInfo(_pPlayer, _pMonster);

		if (_pPlayer->Get_CurStat()->Get_HP() <= 0)
		{
			_pPlayer->Get_CurStat()->Set_HP(0);

			Set_Color(YELLOW);
			cout << "�÷��̾� ������!" << endl;
			Set_Color(GRAY);

			cout << "���� ����" << endl;
			system("pause");
			return;
		}
	}

}

void RenderBattleInfo(CInfo* _pPlayer, CInfo* _pMonster)
{
	system("cls");
	_pPlayer->PrintInfo();
	cout << "====================" << endl;
	cout << "=        VS        =" << endl;
	cout << "====================" << endl;
	_pMonster->PrintInfo();
}

void TryAttack(CInfo* _pAttacker, CInfo* _pTarget)
{
	Set_Color(YELLOW);
	cout << _pAttacker->Get_Name() << "�� ����" << endl;
	Set_Color(GRAY);

	int AttackerDice = RollDice(_pAttacker->Get_CurStat()->Get_DEX());
	int TargetDice = RollDice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
		Set_Color(RED);
		cout << _pAttacker->Get_Name() << "�� ���� ����." << endl;
		Set_Color(GRAY);
		cout << endl;

		int AttackerDice_LUK = RollDice(_pAttacker->Get_CurStat()->Get_LUK());
		int TargetDice_LUK = RollDice(_pTarget->Get_CurStat()->Get_LUK());

		if (AttackerDice_LUK > TargetDice_LUK)
		{
			cout << _pAttacker->Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
			cout << _pTarget->Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;
			
			_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
			Set_Color(RED);
			cout << _pAttacker->Get_Name() << "�� ������ �޼ҿ� ����." << endl;
			Set_Color(GRAY);

			cout << endl;
		}

		system("pause");
	}
	else
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;
		Set_Color(YELLOW);
		cout << _pAttacker->Get_Name() << "�� ���� ������." << endl;
		Set_Color(GRAY);
		cout << endl;
		system("pause");
	}
}
 
int SelectItem(CInfo* _pPlayer, CInfo* _pMonster)
{
	RenderBattleInfo(_pPlayer, _pMonster);

	int iInput(0);

	while ((true))
	{
		RenderBattleInfo(_pPlayer, _pMonster);
		
		_pPlayer->Get_Inven()->PrintAll();
		cout << "����� ������ ����(���=0): ";
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		if (iInput == 0)
		{
			return _ERROR;
		}
		
		//������ ��� �����۰�
		//�ҷ������ ���� ��������
		//�Լ� ������ ���� �޶� ������.
		// 
		//�ҷ� ���� �Ҷ� �ٽ� ��ƾ��ϳ�?
		CItem selectedItem = _pPlayer->Get_Inven()->Get_ItemArray()[iInput - 1];
		selectedItem.Use(_pPlayer, _pMonster);

		RenderBattleInfo(_pPlayer, _pMonster);
		//system("pause");
		return SUCCESS;
	}

}

void LoadCharacter(CInfo** _pPlayer)
{
	*_pPlayer = new CInfo;

	FILE* pLoadFile(nullptr);
	if (fopen_s(&pLoadFile, "../Data/Save.txt", "rb") == 0)
	{//���� ã�� ����
		size_t iResult(0);
		iResult = fread(*_pPlayer, sizeof(CInfo), 1, pLoadFile);
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

void SaveCharacter(CInfo* _pPlayer)
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//�� ���� ���� ����

		size_t iResult(0);
		iResult = fwrite(_pPlayer, sizeof(CInfo), 1, pSaveFile);
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

void Run_TextRPG()
{
	srand(unsigned(time(NULL)));

	CInfo* pPlayer(nullptr);
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