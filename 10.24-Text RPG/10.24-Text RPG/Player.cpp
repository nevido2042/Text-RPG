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

        //cout << "�õ� Ƚ��: " << CPlayer::iTryCount << endl;
        
        Set_Color(YELLOW);
        cout << Get_Info().Get_Gold() << 'G' << endl;
        Set_Color(GRAY);
        
        cout << "Day - " << Get_Info().Get_Day() << endl;
        cout << "������ġ: ����ó" << endl;
        LINE_LINE;
        cout << " [1] �޽�" << endl;
        cout << " [2] ����" << endl;
        cout << " [3] ����ǰ" << endl;
        cout << " [4] ���â(������)" << endl;
        cout << " [5] ����" << endl;
        cout << " [6] ���� & ����" << endl;
        cout << " [999] ġƮ" << endl;
        LINE_LINE;
        
        
        if (_pInputManager-> Receive_Input() == INPUT_ERROR)
        {
        	continue;
        }
        
        switch (_pInputManager->Get_Input())
        {
        case Rest:
        	//�޽�
        	Get_Info().ResetStat();
        	Get_Info().IncreaseDay();
            _pMerchant->Set_Merchant_Inven();
        	break;
        
        case Adventure:
        	//����
        	if (Get_Info().Get_CurStat()->Get_HP() == 0)
        	{
        		cout << "�޽��� �ʿ�." << endl;
        		system("pause");
        		continue;
        	}
        
        	Select_Dungeon(_pInputManager);
        
        	break;
        
        case Inventory:
        	//����ǰ
        	system("cls");
        
        	Select_Item(_pInputManager, nullptr);
        
        	break;
        case Equipment:
            //���â
            Open_Equipment(_pInputManager);
            break;

        case Shop:
        	//����
            _pMerchant->Open_Shop(this, _pInputManager);
        	break;
        case Save_Exit:
        	//����&����
        	//Save_Player();
        	//SAFE_DELETE(m_pPlayer);
        	//SAFE_DELETE(m_pMerchant);
        	return SUCCESS;
        case Cheat:
        	//ġƮ
        	Get_Info().AddGold(999);
            Get_Info().Get_Inven()->AddItem(new CRedPotion("���� ����", 50)/*g_RedPotion*/);
            Get_Info().Get_Inven()->AddItem(new CSword_Of_Legend("������ ��", 500)/*g_Sword_Of_Legend*/);

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

        cout << "������ ǰ���� ��ȣ�� ����(���=0)" << endl;
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
            cout << "�������� �����մϴ�." << endl;
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

        cout << "�Ȱ���� ǰ���� ��ȣ�� ����(���=0)" << endl;
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
    cout << Get_Info().Get_Name() << "�� ����" << endl;
    Set_Color(GRAY);

    int AttackerDice = Roll_Dice(Get_Info().Get_CurStat()->Get_DEX());
    int TargetDice = _pTarget->Roll_Dice(_pTarget->Get_Info().Get_CurStat()->Get_DEX());

    if (AttackerDice > TargetDice)
    {
        cout << Get_Info().Get_Name() << " Dice_DEX: " << AttackerDice << endl;
        cout << _pTarget->Get_Info().Get_Name() << " Dice_DEX: " << TargetDice << endl;

        _pTarget->Get_Info().Get_CurStat()->Add_HP(-Get_Info().Get_CurStat()->Get_STR());
        Set_Color(RED);
        cout << Get_Info().Get_Name() << "�� ���� ����." << endl;
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
            cout << Get_Info().Get_Name() << "�� ������ �޼ҿ� ����." << endl;
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
        cout << Get_Info().Get_Name() << "�� ���� ������." << endl;
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

int CPlayer::Select_Item(CInputManager* _InputManager, CInfo* _pTarget)//entitiy�� �ٲ� ����
{
    //Render_Battle_Info();

    while ((true))
    {
        //Render_Battle_Info();

        Get_Info().Get_Inven()->PrintAll();
        cout << "����� ������ ����(���=0): ";
        if (_InputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_InputManager->Get_Input() == 0)
        {
            return CANCLE;
        }

        //������ ��� �����۰�
        //�ҷ������ ���� ��������
        //�Լ� ������ ���� �޶� ������.
        // 
        //�ҷ� ���� �Ҷ� �ٽ� ��ƾ��ϳ�?
        CItem* selectedItem = Get_Info().Get_Inven()->Get_ItemArray()[_InputManager->Get_Input() - 1];
        selectedItem->Use(&Get_Info(), _pTarget); //Info�� �Ű������� �ƴ϶� �÷��̾�, ���� �Ǿ�� �Ұ� ���� ����

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
        cout << "����� ������ ����(���=0): ";
        if (_InputManager->Receive_Input() == INPUT_ERROR)
        {
            continue;
        }

        if (_InputManager->Get_Input() == 0)
        {
            return CANCLE;
        }

        //������ ��� �����۰�
        //�ҷ������ ���� ��������
        //�Լ� ������ ���� �޶� ������.
        // 
        //�ҷ� ���� �Ҷ� �ٽ� ��ƾ��ϳ�?
        int iIndex = _InputManager->Get_Input() - 1;
        CItem* selectedItem = Get_Info().Get_Inven()->Get_ItemArray()[iIndex];

        int iResult(0);

        iResult = selectedItem->Equip(this); //Info�� �Ű������� �ƴ϶� �÷��̾�, ���� �Ǿ�� �Ұ� ���� ����

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
        //���â ���
        LINE_LINE;
        cout << "[1] �Ӹ�: " << endl;
        cout << "[2] ����: " << endl;
        cout << "[3] ����: " << endl;
        cout << "[4] �Ź�: " << endl;

        cout << "[5] ����: ";
        if (m_Weapon != nullptr)
        {
            cout << m_Weapon->Get_Name();
        }
        cout << endl;

        LINE_LINE;

        //system("pause");


        cout << endl;
        cout << "�����ϰ� ���� ������ ����(���=0)" << endl;
        //�����ϰ���� ���� ����
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
