#include "pch.h"
#include "Player.h"
#include "Dungeon.h"
#include "Merchant.h"
#include "Enemy.h"
#include "item_List.h"

//int CPlayer::iTryCount = 100;
extern CRedPotion g_RedPotion;
extern CSword_Of_Legend g_Sword_Of_Legend;


CPlayer::CPlayer()
    :m_Head(nullptr), m_Top(nullptr), m_Bottom(nullptr),
    m_Shoes(nullptr), m_Weapon(nullptr)
{
    //m_pInfo = nullptr;
}

CPlayer::~CPlayer()
{
    Release();
}

//CInfo& CPlayer::Get_Info()
//{
//    return *m_pInfo;
//}

//void CPlayer::Set_Info(CInfo* _pInfo)
//{
//    if (m_pInfo != nullptr)
//    {
//        PRINT_ERROR;
//    }
//
//    m_pInfo = _pInfo;
//}

void CPlayer::Initialize()
{
    CEntity::Initialize();
    //Set_Info(new CInfo);
    //Get_Info().Initialize();
}

void CPlayer::Release()
{
    //SAFE_DELETE(m_pInfo);
}

int CPlayer::Select_Task(CInputManager* _pInputManager, CMerchant* _pMerchant)
{
    enum TASK { Rest = 1, Adventure, Inventory, Equipment, Shop, Save_Exit, Cheat = 999 };

    while (true)
    {
        system("cls");
        Get_Info().PrintInfo();

        //cout << "시도 횟수: " << CPlayer::iTryCount << endl;
        
        Set_Color(YELLOW);
        cout << Get_Info().Get_Gold() << 'G' << endl;
        Set_Color(GRAY);
        
        cout << "Day - " << Get_Info().Get_Day() << endl;
        cout << "현재위치: 은신처" << endl;
        LINE_LINE;
        cout << " [1] 휴식" << endl;
        cout << " [2] 모험" << endl;
        cout << " [3] 소지품" << endl;
        cout << " [4] 장비창(공사중)" << endl;
        cout << " [5] 상점" << endl;
        cout << " [6] 저장 & 종료" << endl;
        cout << " [999] 치트" << endl;
        LINE_LINE;
        
        
        if (_pInputManager-> Receive_Input() == INPUT_ERROR)
        {
        	continue;
        }
        
        switch (_pInputManager->Get_Input())
        {
        case Rest:
        	//휴식
        	Get_Info().ResetStat();
        	Get_Info().IncreaseDay();
            _pMerchant->Set_Merchant_Inven();
        	break;
        
        case Adventure:
        	//모험
        	if (Get_Info().Get_CurStat()->Get_HP() == 0)
        	{
        		cout << "휴식이 필요." << endl;
        		system("pause");
        		continue;
        	}
        
        	Select_Dungeon(_pInputManager);
        
        	break;
        
        case Inventory:
        	//소지품
        	system("cls");
        
        	Select_Item(_pInputManager, nullptr);
        
        	break;
        case Equipment:
            //장비창
            Open_Equipment(_pInputManager);
            break;

        case Shop:
        	//상점
            _pMerchant->Open_Shop(this, _pInputManager);
        	break;
        case Save_Exit:
        	//저장&종료
        	//Save_Player();
        	//SAFE_DELETE(m_pPlayer);
        	//SAFE_DELETE(m_pMerchant);
        	return SUCCESS;
        case Cheat:
        	//치트
        	Get_Info().AddGold(999);
            Get_Info().Get_Inven()->AddItem(new CRedPotion("빨간 물약", 50)/*g_RedPotion*/);
            Get_Info().Get_Inven()->AddItem(new CSword_Of_Legend("전설의 검", 500)/*g_Sword_Of_Legend*/);

        	break;
        default:
        	break;
        }
    }

    PRINT_ERROR;
    return _ERROR;
}

void CPlayer::Select_Dungeon(CInputManager* _pInputManager)
{
    while (true)
    {
        if (Get_Info().Get_CurStat()->Get_HP() == 0)
        {
            return;
        }

        system("cls");
        Get_Info().PrintInfo();
        cout << "현재위치: 갈래길" << endl;
        cout << "<모험 장소 선택>" << endl;
        LINE_LINE;
        Set_Color(GREEN);
        cout << "[1] 초원 " << endl; // 2.산 3.동굴 4.복귀" << endl;
        Set_Color(GRAY);

        Set_Color(YELLOW);
        cout << "[2] 산 " << endl;
        Set_Color(GRAY);

        Set_Color(RED);
        cout << "[3] 동굴 " << endl;
        Set_Color(GRAY);

        cout << "[4] 은신처로 돌아가기 " << endl;
        LINE_LINE;

        if (_pInputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        switch (_pInputManager->Get_Input())
        {
        case 1:
        {
            CDungeon* Dungeon = new CDungeon(this, CDungeon::Grassland, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 2:
        {
            CDungeon* Dungeon = new CDungeon(this, CDungeon::Mountain, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 3:
        {
            CDungeon* Dungeon = new CDungeon(this, CDungeon::Cave, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 4:
            return;
        default:
            break;
        }
    }
}

void CPlayer::Buy_Item(CMerchant* _pMerchant, CInputManager* _pInputManager)
{
    while (true)
    {
        _pMerchant->Render_Shop(this);

        cout << "사고싶은 품목의 번호를 선택(취소=0)" << endl;
        if (_pInputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_pInputManager->Get_Input() == 0)
        {
            break;
        }

        CItem* item = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];

        int iItemValue = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1]->Get_Value();
        if (Get_Info().Get_Gold() >= iItemValue)
        {
            Get_Info().AddGold(-iItemValue);
        }
        else
        {
            cout << "소지금이 부족합니다." << endl;
            system("pause");
            continue;
        }

        if (_pMerchant->Get_Info().Get_Inven()->RemoveItem(_pInputManager->Get_Input() - 1) == SUCCESS)
        {
            Get_Info().Get_Inven()->AddItem(item);
        }
    }
}

void CPlayer::Sell_Item(CMerchant* _pMerchant, CInputManager* _pInputManager)
{
    while (true)
    {
        _pMerchant->Render_Shop(this);

        cout << "팔고싶은 품목의 번호를 선택(취소=0)" << endl;
        if (_pInputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_pInputManager->Get_Input() == 0)
        {
            break;
        }

        CItem* pItem = Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];
        if (Get_Info().Get_Inven()->RemoveItem(_pInputManager->Get_Input() - 1) == SUCCESS)
        {
            Get_Info().AddGold((*pItem).Get_Value());
            _pMerchant->Get_Info().Get_Inven()->AddItem(pItem);
        }
    }
}

void CPlayer::Try_Attack(CEnemy* _pTarget)
{
    Set_Color(YELLOW);
    cout << Get_Info().Get_Name() << "의 공격" << endl;
    Set_Color(GRAY);

    int AttackerDice = Roll_Dice(Get_Info().Get_CurStat()->Get_DEX());
    int TargetDice = _pTarget->Roll_Dice(_pTarget->Get_Info().Get_CurStat()->Get_DEX());

    if (AttackerDice > TargetDice)
    {
        cout << Get_Info().Get_Name() << " Dice_DEX: " << AttackerDice << endl;
        cout << _pTarget->Get_Info().Get_Name() << " Dice_DEX: " << TargetDice << endl;

        _pTarget->Get_Info().Get_CurStat()->Add_HP(-Get_Info().Get_CurStat()->Get_STR());
        Set_Color(RED);
        cout << Get_Info().Get_Name() << "의 공격 명중." << endl;
        Set_Color(GRAY);
        cout << endl;

        int AttackerDice_LUK = Roll_Dice(Get_Info().Get_CurStat()->Get_LUK());
        int TargetDice_LUK = _pTarget->Roll_Dice(_pTarget->Get_Info().Get_CurStat()->Get_LUK());

        if (AttackerDice_LUK > TargetDice_LUK)
        {
            cout << Get_Info().Get_Name() << " Dice_LUK: " << AttackerDice_LUK << endl;
            cout << _pTarget->Get_Info().Get_Name() << " Dice_LUK: " << TargetDice_LUK << endl;

            _pTarget->Get_Info().Get_CurStat()->Add_HP(-Get_Info().Get_CurStat()->Get_STR());
            Set_Color(RED);
            cout << Get_Info().Get_Name() << "의 공격이 급소에 명중." << endl;
            Set_Color(GRAY);

            cout << endl;
        }

        system("pause");
    }
    else
    {
        cout << Get_Info().Get_Name() << " Dice_DEX: " << AttackerDice << endl;
        cout << _pTarget->Get_Info().Get_Name() << " Dice_DEX: " << TargetDice << endl;
        Set_Color(YELLOW);
        cout << Get_Info().Get_Name() << "의 공격 빗나감." << endl;
        Set_Color(GRAY);
        cout << endl;
        system("pause");
    }
}

int CPlayer::Roll_Dice(int _iValue)
{
    if (_iValue == 0)
        return 0;

    return rand() % _iValue + 1;
}

int CPlayer::Select_Item(CInputManager* _InputManager, CInfo* _pTarget)//entitiy로 바꿀 예정
{
    //Render_Battle_Info();

    while ((true))
    {
        //Render_Battle_Info();

        Get_Info().Get_Inven()->PrintAll();
        cout << "사용할 아이템 선택(취소=0): ";
        if (_InputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_InputManager->Get_Input() == 0)
        {
            return CANCLE;
        }

        //게임중 얻는 아이템과
        //불러오기로 들어온 아이템의
        //함수 포인터 값이 달라서 터진다.
        // 
        //불러 오기 할때 다시 담아야하나?
        CItem* selectedItem = Get_Info().Get_Inven()->Get_ItemArray()[_InputManager->Get_Input() - 1];
        selectedItem->Use(&Get_Info(), _pTarget); //Info가 매개변수가 아니라 플레이어, 적이 되어야 할거 같은 느낌

        //Render_Battle_Info();

        return SUCCESS;
    }
}

int CPlayer::Equip_Item(CInputManager* _InputManager, CItem** _Part)
{
    //Render_Battle_Info();

    while ((true))
    {
        //Render_Battle_Info();

        Get_Info().Get_Inven()->PrintAll();
        cout << "사용할 아이템 선택(취소=0): ";
        if (_InputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_InputManager->Get_Input() == 0)
        {
            return CANCLE;
        }

        //게임중 얻는 아이템과
        //불러오기로 들어온 아이템의
        //함수 포인터 값이 달라서 터진다.
        // 
        //불러 오기 할때 다시 담아야하나?
        int iIndex = _InputManager->Get_Input() - 1;
        CItem* selectedItem = Get_Info().Get_Inven()->Get_ItemArray()[iIndex];

        int iResult(0);

        iResult = selectedItem->Equip(this); //Info가 매개변수가 아니라 플레이어, 적이 되어야 할거 같은 느낌

        if (iResult == SUCCESS)
        {
            *_Part = selectedItem;
            //Render_Battle_Info();

            Get_Info().Get_Inven()->RemoveItem(iIndex);
        }

        return SUCCESS;
    }
}

void CPlayer::Open_Equipment(CInputManager* _InputManager)
{
    enum EQUIP { Head = 1, Top, Bottom, Shoes, Weapon };
    while (true)
    {
        system("cls");
        //장비창 출력
        LINE_LINE;
        cout << "[1] 머리: " << endl;
        cout << "[2] 상의: " << endl;
        cout << "[3] 하의: " << endl;
        cout << "[4] 신발: " << endl;

        cout << "[5] 무기: ";
        if (m_Weapon != nullptr)
        {
            cout << m_Weapon->Get_Name();
        }
        cout << endl;

        LINE_LINE;

        //system("pause");


        cout << endl;
        cout << "변경하고 싶은 부위를 선택(취소=0)" << endl;
        //변경하고싶은 부위 선택
        if (_InputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_InputManager->Get_Input() == 0)
        {
            return;
        }

        switch (_InputManager->Get_Input())
        {
        case Head:
            break;

        case Top:
            break;

        case Bottom:
            break;

        case Shoes:
            break;

        case Weapon:
            system("cls");
            Equip_Item(_InputManager, &m_Weapon);
            break;

        default:
            break;
        }
    }
 
}
