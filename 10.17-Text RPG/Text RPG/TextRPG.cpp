#include "pch.h"
#include "TextRPG.h"
#include "misc.h"

void CreateCharacter(INFO** _ppPlayer)
{
	while (true)
	{
		system("cls");
		//cout << "====================" << endl;
		cout << "<캐릭터 생성>" << endl;
		cout << endl;
		*_ppPlayer = new INFO;
		cout << "이름" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> (*_ppPlayer)->szName; //위험한 짓인가? //그래서 저장공간 두배로 함 일단

		if (strlen((*_ppPlayer)->szName) >= NAME_LEN)
		{
			cout << "이름 길이 초과!" << endl;
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
		cout << "<능력치 설정>" << endl;
		cout << endl;

		_pPlayer->PrintName();
		_pPlayer->stat.PrintALL();

		cout << "====================" << endl;
		cout << "1.주사위돌리기 2.결정" << endl;

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
		cout << "현재위치: 은신처" << endl;
		cout << "<행동 결정>" << endl;
		cout << " 1.휴식 2.모험 3.메인메뉴 4.저장하기" << endl;

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
				cout << "휴식이 필요." << endl;
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
	cout << "입력: ";
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
		cout << "현재위치: 갈래길" << endl;
		cout << "<모험 장소 선택>" << endl;
		cout << "1.초원 2.산 3.동굴 4.복귀" << endl;

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
	if (!cin) //자료형이 다른 값이 들어 오는 지 체크
	{
		cin.clear();

		while (cin.get() != '\n');

		//cout << "잘못된 입력" << endl;
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
		cout << "현재 위치: 초원" << endl;
		SetColor(GRAY);
		cout << "[행동 선택]" << endl;
		cout << "1.대기 2.탐색 3.복귀" << endl;
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

	cout << "몬스터와 마주했다." << endl;

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
		cout << "몬스터의 선제 공격!" << endl;
		cout << endl;
		system("pause");

		if (_pPlayer->curStat.iHP <= 0)
		{
			RenderBattleInfo(_pPlayer, _pMonster);

			_pPlayer->curStat.iHP = 0;
			cout << "플레이어 쓰러짐!" << endl;
			cout << endl;

			system("pause");

			return;
		}
	}

	while (true)
	{
		RenderBattleInfo(_pPlayer, _pMonster);

		//cout << "몬스터를 발견함." << endl;
		cout << "[행동 선택]" << endl;
		cout << "1.공격 2.도망" << endl;
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

			cout << "플레이어의 공격 명중.";
			cout << endl;

			if (_pMonster->curStat.iHP <= 0)
			{
				_pMonster->curStat.iHP = 0;

				cout << "몬스터 쓰러짐!" << endl;
				cout << "전투 종료" << endl;
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

		cout << "몬스터의 공격!" << endl;
		cout << endl;

		system("pause");

		_pPlayer->curStat.iHP -= _pMonster->curStat.iSTR;

		RenderBattleInfo(_pPlayer, _pMonster);

		cout << "몬스터의 공격이 명중했다.";
		cout << endl;

		if (_pPlayer->curStat.iHP <= 0)
		{
			_pPlayer->curStat.iHP = 0;

			cout << "플레이어 쓰러짐!" << endl;
			cout << "전투 종료" << endl;
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
	{//파일 찾기 성공
		size_t iResult(0);
		iResult = fread(*_pPlayer, sizeof(INFO), 1, pLoadFile);
		if (iResult != 1)
		{
			cout << "불러오기 오류" << endl;
			system("pause");
		}

		fclose(pLoadFile);
	}
	else
	{
		cout << "저장 파일 찾지 못함." << endl;
		system("pause");
	}

}

void SaveCharacter(INFO* _pPlayer)
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//새 파일 생성 성공

		size_t iResult(0);
		iResult = fwrite(_pPlayer, sizeof(INFO), 1, pSaveFile);
		if (iResult != 1)//fwirte는 카운트를 반환 하는구나
		{
			cout << "iResult: " << iResult << endl;
			//cout << "INFO: " << sizeof(INFO) << endl;

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

void Run_TextRPG()
{
	srand(unsigned(time(NULL)));

	INFO* pPlayer(nullptr);
	int iInput(0);

	while (true)
	{
		cin.clear();

		system("cls");
		cout << "[메인 메뉴]" << endl;
		cout << endl;

		cout << "1.새 게임 2.게임종료 3.이어하기" << endl;
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