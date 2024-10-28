#include "pch.h"
#include "Player.h"
#include "Dungeon.h" //나중에 빼야할 듯

enum DUNGEON { Grassland = 1, Mountain, Cave };//나중에 빼야할 듯

CPlayer::CPlayer()
{
    m_pInfo = nullptr;
}

CPlayer::~CPlayer()
{
    Release();
}

CInfo& CPlayer::Get_Info()
{
    return *m_pInfo;
}

void CPlayer::Set_Info(CInfo* _pInfo)
{
    m_pInfo = _pInfo;
}

void CPlayer::Initialize()
{
    Set_Info(new CInfo);
    Get_Info().Initialize();
}

void CPlayer::Release()
{
    SAFE_DELETE(m_pInfo);
}

int CPlayer::Select_Task(CInputManager* _pInputManager, CMerchant* _pMerchant)
{
    while (true)
    {
        system("cls");
        Get_Info().PrintInfo();
        
        Set_Color(YELLOW);
        cout << Get_Info().Get_Gold() << 'G' << endl;
        Set_Color(GRAY);
        
        cout << "Day - " << Get_Info().Get_Day() << endl;
        cout << "현재위치: 은신처" << endl;
        LINE_LINE;
        cout << " [1] 휴식" << endl;
        cout << " [2] 모험" << endl;
        cout << " [3] 소지품" << endl;
        cout << " [4] 상점" << endl;
        cout << " [5] 저장 & 종료" << endl;
        cout << " [999] 치트" << endl;
        LINE_LINE;
        
        
        if (_pInputManager-> Receive_Input() == INPUT_ERROR)
        {
        	continue;
        }
        
        switch (_pInputManager->Get_Input())
        {
        case 1:
        	//휴식
        	Get_Info().ResetStat();
        	Get_Info().IncreaseDay();
            _pMerchant->Set_Merchant_Inven();
        	break;
        
        case 2:
        	//모험
        	if (Get_Info().Get_CurStat()->Get_HP() == 0)
        	{
        		cout << "휴식이 필요." << endl;
        		system("pause");
        		continue;
        	}
        
        	Select_Dungeon(_pInputManager);
        
        	break;
        
        case 3:
        	//소지품
        	system("cls");
        
        	Get_Info().Select_Item(_pInputManager, nullptr);
        
        	break;
        case 4:
        	//상점
            _pMerchant->Open_Shop(this, _pInputManager);
        	break;
        case 5:
        	//저장&종료
        	//Save_Player();
        	//SAFE_DELETE(m_pPlayer);
        	//SAFE_DELETE(m_pMerchant);
        	return SUCCESS;
        case 999:
        	//치트
        	Get_Info().AddGold(999);
        	extern CItem redPotion;
        	Get_Info().Get_Inven()->AddItem(redPotion);
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
            CDungeon* Dungeon = new CDungeon(&Get_Info(), Grassland, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 2:
        {
            CDungeon* Dungeon = new CDungeon(&Get_Info(), Mountain, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 3:
        {
            CDungeon* Dungeon = new CDungeon(&Get_Info(), Cave, _pInputManager);
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

        CItem item = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];

        int iItemValue = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1].Get_Value();
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

        CItem item = Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];
        if (Get_Info().Get_Inven()->RemoveItem(_pInputManager->Get_Input() - 1) == SUCCESS)
        {
            Get_Info().AddGold(item.Get_Value());
            _pMerchant->Get_Info().Get_Inven()->AddItem(item);
        }
    }
}
