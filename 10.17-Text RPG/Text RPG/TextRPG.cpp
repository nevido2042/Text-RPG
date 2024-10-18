#include "pch.h"
#include "TextRPG.h"
#include "misc.h"

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
	int iInput(0);

	while (true)
	{
		system("cls");
		_pPlayer->PrintInfo();
		cout << "Day-" << _pPlayer->iDay << endl;
		cout << "������ġ: ����ó" << endl;
		cout << "<�ൿ ����>" << endl;
		cout << " 1.�޽� 2.���� 3.���θ޴� 4.�����ϱ�" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			_pPlayer->ResetStat();
			_pPlayer->iDay++;
			break;

		case 2:
			if (_pPlayer->curStat.iHP == 0)
			{
				cout << "�޽��� �ʿ�." << endl;
				system("pause");
				continue;
			}

			SelectDungeon(_pPlayer);

			break;
		case 3:
			delete _pPlayer;
			_pPlayer = nullptr;

			return;
		case 4:
			SaveCharacter(_pPlayer);
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

	return 0;
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
			Enter_Grassland(_pPlayer);
			break;
		case 2:
			break;
		case 3:
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

	return 0;
}

void Enter_Grassland(INFO* _pPlayer)
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

		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		SetColor(GREEN);
		cout << "���� ��ġ: �ʿ�" << endl;
		SetColor(GRAY);
		cout << "[�ൿ ����]" << endl;
		cout << "1.��� 2.Ž�� 3.����" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}
		switch (iInput)
		{
		case 1:
			//_pPlayer->ResetStat();
			break;
		case 2:
			FaceMonster(_pPlayer);
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void FaceMonster(INFO* _pPlayer)
{
	INFO* pMonster = new INFO;
	strcpy_s(pMonster->szName, "???");
	pMonster->stat.SetStatRandom();
	pMonster->ResetStat();

	RenderBattleInfo(_pPlayer, pMonster);

	cout << "���Ϳ� �����ߴ�." << endl;

	system("pause");

	StartBattle(_pPlayer, pMonster);

	/*if (_pPlayer->curStat.iHP == 0)
	{
		return;
	}*/
	delete pMonster;
	pMonster = nullptr;

	return;
}

void StartBattle(INFO* _pPlayer, INFO* _pMonster)
{
	int iInput(0);

	if (_pMonster->curStat.iDEX > _pPlayer->curStat.iDEX)
	{
		RenderBattleInfo(_pPlayer, _pMonster);

		_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;
		cout << "������ ���� ����!" << endl;
		cout << endl;
		system("pause");

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
		cout << "1.���� 2.����" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			_pMonster->curStat.iHP -= _pPlayer->curStat.iSTR;

			RenderBattleInfo(_pPlayer, _pMonster);
			cout << endl;

			cout << "�÷��̾��� ���� ����.";
			cout << endl;

			if (_pMonster->curStat.iHP <= 0)
			{
				_pMonster->curStat.iHP = 0;

				cout << "���� ������!" << endl;
				cout << "���� ����" << endl;
				system("pause");
				return;
			}

			system("pause");

			break;
		case 2:
			return;
		default:
			continue;
		}

		RenderBattleInfo(_pPlayer, _pMonster);

		cout << "������ ����!" << endl;
		cout << endl;

		system("pause");

		_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;

		RenderBattleInfo(_pPlayer, _pMonster);

		cout << "������ ������ �����ߴ�.";
		cout << endl;

		if (_pPlayer->curStat.iHP <= 0)
		{
			_pPlayer->curStat.iHP = 0;

			cout << "�÷��̾� ������!" << endl;
			cout << "���� ����" << endl;
			system("pause");
			return;
		}

		system("pause");

		//system("cls");
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
		cin.clear();

		system("cls");
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