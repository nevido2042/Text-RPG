#include "pch.h"
#include "Player.h"
#include "Dungeon.h" //���߿� ������ ��
#include "Merchant.h"
#include "Enemy.h"

enum DUNGEON { Grassland = 1, Mountain, Cave };//���߿� ������ ��

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
        cout << "������ġ: ����ó" << endl;
        LINE_LINE;
        cout << " [1] �޽�" << endl;
        cout << " [2] ����" << endl;
        cout << " [3] ����ǰ" << endl;
        cout << " [4] ����" << endl;
        cout << " [5] ���� & ����" << endl;
        cout << " [999] ġƮ" << endl;
        LINE_LINE;
        
        
        if (_pInputManager-> Receive_Input() == INPUT_ERROR)
        {
        	continue;
        }
        
        switch (_pInputManager->Get_Input())
        {
        case 1:
        	//�޽�
        	Get_Info().ResetStat();
        	Get_Info().IncreaseDay();
            _pMerchant->Set_Merchant_Inven();
        	break;
        
        case 2:
        	//����
        	if (Get_Info().Get_CurStat()->Get_HP() == 0)
        	{
        		cout << "�޽��� �ʿ�." << endl;
        		system("pause");
        		continue;
        	}
        
        	Select_Dungeon(_pInputManager);
        
        	break;
        
        case 3:
        	//����ǰ
        	system("cls");
        
        	Select_Item(_pInputManager, nullptr);
        
        	break;
        case 4:
        	//����
            _pMerchant->Open_Shop(this, _pInputManager);
        	break;
        case 5:
        	//����&����
        	//Save_Player();
        	//SAFE_DELETE(m_pPlayer);
        	//SAFE_DELETE(m_pMerchant);
        	return SUCCESS;
        case 999:
        	//ġƮ
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
            CDungeon* Dungeon = new CDungeon(this, Grassland, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 2:
        {
            CDungeon* Dungeon = new CDungeon(this, Mountain, _pInputManager);
            Dungeon->Initialize();
            SAFE_DELETE(Dungeon);
            break;
        }

        case 3:
        {
            CDungeon* Dungeon = new CDungeon(this, Cave, _pInputManager);
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

        CItem item = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];

        int iItemValue = _pMerchant->Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1].Get_Value();
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

        CItem item = Get_Info().Get_Inven()->Get_ItemArray()[_pInputManager->Get_Input() - 1];
        if (Get_Info().Get_Inven()->RemoveItem(_pInputManager->Get_Input() - 1) == SUCCESS)
        {
            Get_Info().AddGold(item.Get_Value());
            _pMerchant->Get_Info().Get_Inven()->AddItem(item);
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

int CPlayer::Select_Item(CInputManager* _InputManager, CInfo* _pTarget)
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
        CItem selectedItem = Get_Info().Get_Inven()->Get_ItemArray()[_InputManager->Get_Input() - 1];
        selectedItem.Use(&Get_Info(), _pTarget); //Info�� �Ű������� �ƴ϶� �÷��̾�, ���� �Ǿ�� �Ұ� ���� ����

        //Render_Battle_Info();

        return SUCCESS;
    }
}
