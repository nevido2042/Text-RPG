#include "pch.h"
#include "TextRPG.h"
#include "misc.h"

void CreateCharacter(CInfo** _ppPlayer)
{
	while (true)
	{
		system("cls");
		LINE_LINE;
		cout << "<캐릭터 생성>" << endl;
		cout << endl;
		*_ppPlayer = new CInfo;
		cout << "이름" << '(' << NAME_LEN << "Byte" << ')' << ": ";
		cin >> (*_ppPlayer)->Get_Name(); //위험한 짓인가? //그래서 저장공간 두배로 함 일단

		if (strlen((*_ppPlayer)->Get_Name()) >= NAME_LEN)
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

void SetSTAT(CInfo* _pPlayer)
{
	int iInput(0);
	_pPlayer->Get_Stat()->SetStatRandom();

	while (true)
	{
		system("cls");
		LINE_LINE;
		cout << "<능력치 설정>" << endl;
		cout << endl;

		_pPlayer->PrintName();
		_pPlayer->Get_Stat()->PrintALL();

		LINE_LINE;
		cout << "1.주사위돌리기 2.결정" << endl;

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
		cout << "현재위치: 은신처" << endl;
		cout << "<행동 결정>" << endl;
		cout << " 1.휴식 2.모험 3.소지품 4.상점 5.저장&종료 999.치트" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//휴식
			_pPlayer->ResetStat();
			_pPlayer->IncreaseDay();
			pMerchant->Get_Inven()->SetMerchantInven();
			break;

		case 2:
			//모험
			if (_pPlayer->Get_CurStat()->Get_HP() == 0)
			{
				cout << "휴식이 필요." << endl;
				system("pause");
				continue;
			}

			SelectDungeon(_pPlayer);

			break;
			
		case 3:
			//소지품
			system("cls");
			_pPlayer->ResetStat();
			_pPlayer->Get_Inven()->PrintAll();
			system("pause");
			break;
		case 4:
			//상점
			OpenShop(_pPlayer, pMerchant);
			break;
		case 5:
			//저장&종료
			SaveCharacter(_pPlayer);
			SAFE_DELETE(_pPlayer);
			SAFE_DELETE(pMerchant);
			return;
		case 999:
			//치트
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
	cout << "입력: ";
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

	//CInfo* merchant = new CInfo; //상인 하루에 한번만 리셋되도록 바꿔야지

	while (true)
	{
		RenderShop(_pPlayer, _pMerchant);

		cout << "1.구매 2.판매 3.나가기" << endl;
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

	cout << "플레이어의 ";
	_pPlayer->Get_Inven()->PrintAll();

	LINE_LINE;

	cout << "상인의";
	_pMerchant->Get_Inven()->PrintAll();

	cout << endl;
}

void BuyItem(CInfo* _pPlayer, CInfo* _pMerchant)
{
	int iInput(0);
	while (true)
	{
		RenderShop(_pPlayer, _pMerchant);

		cout << "사고싶은 품목의 번호를 선택(취소=0)" << endl;
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
			cout << "소지금이 부족합니다." << endl;
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

		cout << "팔고싶은 품목의 번호를 선택(취소=0)" << endl;
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
	if (!cin) //자료형이 다른 값이 들어 오는 지 체크
	{
		cin.clear();

		while (cin.get() != '\n');

		//cout << "잘못된 입력" << endl;
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
			//cout << "플레이어 쓰러짐" << endl;
			//system("pause");
			return;
		}

		system("cls");
		_pPlayer->PrintInfo();

		switch (_iValue)
		{
		case Grassland:
			Set_Color(GREEN);
			cout << "현재 위치: 초원" << endl;
			Set_Color(GRAY);
			break;
		case Mountain:
			Set_Color(YELLOW);
			cout << "현재 위치: 산" << endl;
			Set_Color(GRAY);
			break;
		case Cave:
			Set_Color(RED);
			cout << "현재 위치: 동굴" << endl;
			Set_Color(GRAY);
			break;
		}

		cout << "[행동 선택]" << endl;
		cout << "1.대기 2.탐색 3.복귀" << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}
		switch (iInput)
		{
		case 1:
			//대기
			//_pPlayer->ResetStat();
			_pPlayer->Get_CurStat()->Add_HP(-1);

			break;
		case 2:
			//탐색
			//적 조우, 함정(DEX), 상자(INT)-미믹,보물,함정
			TriggerRandomEvent(_pPlayer, _iValue);
			//FaceMonster(_pPlayer, 2);
			break;
		case 3:
			//복귀
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
//		cout << "현재 위치: 초원" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[행동 선택]" << endl;
//		cout << "1.대기 2.탐색 3.복귀" << endl;
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
//			//cout << "플레이어 쓰러짐" << endl;
//			//system("pause");
//			return;
//		}
//
//		system("cls");
//		_pPlayer->PrintInfo();
//
//		SetPrintColor(YELLOW);
//		cout << "현재 위치: 산" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[행동 선택]" << endl;
//		cout << "1.대기 2.탐색 3.복귀" << endl;
//		if (GetInput(&iInput) == INPUT_ERROR)
//		{
//			continue;
//		}
//		switch (iInput)
//		{
//		case 1:
//			//대기
//			//_pPlayer->ResetStat();
//			_pPlayer->curStat.iHP -= 1;
//
//			break;
//		case 2:
//			//탐색
//			//적 조우, 함정(DEX), 상자(INT)-미믹,보물,함정
//			TriggerRandomEvent(_pPlayer, 2);
//			//FaceMonster(_pPlayer, 2);
//			break;
//		case 3:
//			//복귀
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
//		cout << "현재 위치: 동굴" << endl;
//		SetPrintColor(GRAY);
//
//		cout << "[행동 선택]" << endl;
//		cout << "1.대기 2.탐색 3.복귀" << endl;
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
	cout << "함정(" << _iValue << ")이 작동되었다!" << endl;
	Set_Color(GRAY);

	cout << "주사위 굴리기(DEX)" << endl;
	system("pause");
	cout << endl;

	int iDice_DEX = RollDice(_pPlayer->Get_CurStat()->Get_DEX());
	if (iDice_DEX > _iValue)
	{
		cout << "주사위 결과: " << iDice_DEX << endl;
		Set_Color(YELLOW);
		cout << "재빠른 몸놀림으로 함정을 피했다." << endl;
		Set_Color(GRAY);

		system("pause");
		return;
	}
	else
	{
		_pPlayer->Get_CurStat()->Add_HP(-_iValue);

		cout << "주사위 결과: " << iDice_DEX << endl;
		Set_Color(RED);
		cout << "함정에 피해를 받았다." << endl;
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
		cout << "마법으로 잠긴 상자(" << _iValue << ")를 발견했다._" << endl;
		Set_Color(GRAY);

		cout << "1.마법 풀기(INT) 2.무시하기" << endl;

		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
			//마법 풀기
		{
			int iDice_INT = RollDice(_pPlayer->Get_CurStat()->Get_INT());

			if (iDice_INT > _iValue)
			{
				cout << "주사위 결과: " << iDice_INT << endl;
				Set_Color(YELLOW);
				cout << "상자에 걸린 마법을 제거했다." << endl;
				cout << "보물을 획득 했다." << endl;
				Set_Color(GRAY);

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "보물");
				item.Set_Value(500);
				
				_pPlayer->Get_Inven()->AddItem(item);

				system("pause");
			}
			else
			{
				cout << "주사위 결과: " << iDice_INT << endl;
				Set_Color(YELLOW);
				cout << "마법을 제거하지 못했다." << endl;
				Set_Color(GRAY);

				system("pause");
			}
			return;
		}
		case 2:
			//무시 하기
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
	cout << "몬스터와 마주했다." << endl;
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
		cout << "몬스터의 민첩이 더 높다." << endl;
		Set_Color(YELLOW);
		cout << "몬스터의 선제 공격!" << endl;
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
			cout << "플레이어 쓰러짐!" << endl;
			Set_Color(GRAY);

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
		cout << "1.공격 2.아이템 3.도망 " << endl;
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		switch (iInput)
		{
		case 1:
		{
			//공격
			TryAttack(_pPlayer, _pMonster);

			RenderBattleInfo(_pPlayer, _pMonster);
			cout << endl;

			if (_pMonster->Get_CurStat()->Get_HP() <= 0)
			{
				_pMonster->Get_CurStat()->Set_HP(0);

				Set_Color(YELLOW);
				cout << "몬스터 쓰러짐!" << endl;
				Set_Color(GRAY);

				cout << "전투 종료" << endl;

				CItem item;
				strcpy_s(item.Get_Name(), NAME_LEN, "Test Item");
				item.Set_Value(50);
				cout << "아이템 획득:" << item.Get_Name() << endl;
				_pPlayer->Get_Inven()->AddItem(item);

				system("pause");
				return;
			}

			//system("pause");

			break;
		}
			
		case 2:
			//아이템
			if (SelectItem(_pPlayer, _pMonster) == SUCCESS)
			{
				break;
			}
			else
			{
				continue;
			}
		case 3:
			//도망
		{
			int iPlayerDice = RollDice(_pPlayer->Get_CurStat()->Get_DEX());
			int iMonsterDice = RollDice(_pMonster->Get_CurStat()->Get_DEX());

			if (iPlayerDice > iMonsterDice)
			{
				cout << "PlayerDice: " << iPlayerDice << endl;
				cout << "MonsterDice: " << iMonsterDice << endl;
				
				Set_Color(YELLOW);
				cout << "도망 성공" << endl;
				Set_Color(GRAY);

				system("pause");
				return;

			}
			cout << "PlayerDice: " << iPlayerDice << endl;
			cout << "MonsterDice: " << iMonsterDice << endl;
			Set_Color(YELLOW);
			cout << "도망 실패" << endl;
			Set_Color(GRAY);

			system("pause");
			break;
		}
		default:
			continue;
		}

		Set_Color(YELLOW);
		cout << "적의 턴" << endl;
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
			cout << "플레이어 쓰러짐!" << endl;
			Set_Color(GRAY);

			cout << "전투 종료" << endl;
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
	cout << _pAttacker->Get_Name() << "의 공격" << endl;
	Set_Color(GRAY);

	int AttackerDice = RollDice(_pAttacker->Get_CurStat()->Get_DEX());
	int TargetDice = RollDice(_pTarget->Get_CurStat()->Get_DEX());

	if (AttackerDice > TargetDice)
	{
		cout << _pAttacker->Get_Name() << " Dice_DEX: " << AttackerDice << endl;
		cout << _pTarget->Get_Name() << " Dice_DEX: " << TargetDice << endl;

		_pTarget->Get_CurStat()->Add_HP(-_pAttacker->Get_CurStat()->Get_STR());
		Set_Color(RED);
		cout << _pAttacker->Get_Name() << "의 공격 명중." << endl;
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
			cout << _pAttacker->Get_Name() << "의 공격이 급소에 명중." << endl;
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
		cout << _pAttacker->Get_Name() << "의 공격 빗나감." << endl;
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
		cout << "사용할 아이템 선택(취소=0): ";
		if (GetInput(&iInput) == INPUT_ERROR)
		{
			continue;
		}

		if (iInput == 0)
		{
			return _ERROR;
		}
		
		//게임중 얻는 아이템과
		//불러오기로 들어온 아이템의
		//함수 포인터 값이 달라서 터진다.
		// 
		//불러 오기 할때 다시 담아야하나?
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
	{//파일 찾기 성공
		size_t iResult(0);
		iResult = fread(*_pPlayer, sizeof(CInfo), 1, pLoadFile);
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

void SaveCharacter(CInfo* _pPlayer)
{
	FILE* pSaveFile(nullptr);

	if (fopen_s(&pSaveFile, "../Data/Save.txt", "wb") == 0)
	{//새 파일 생성 성공

		size_t iResult(0);
		iResult = fwrite(_pPlayer, sizeof(CInfo), 1, pSaveFile);
		if (iResult != 1)//fwirte는 카운트를 반환 하는구나
		{
			cout << "iResult: " << iResult << endl;
			//cout << "CInfo: " << sizeof(CInfo) << endl;

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

	CInfo* pPlayer(nullptr);
	int iInput(0);

	while (true)
	{
		system("cls");
		cout << "<TEXT RPG>" << endl;
		cout << endl;

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