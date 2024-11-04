#include "pch.h"
#include "Merchant.h"
#include "Player.h"
#include "item_List.h"

extern CRedPotion g_RedPotion;
extern CSmall_RedPotion g_Small_RedPotion;
extern CSword_Of_Legend g_Sword_Of_Legend;

CMerchant::CMerchant()
	//:m_pInfo(nullptr)
{
    //m_pInfo = nullptr;
}

CMerchant::~CMerchant()
{
    Release();
}

//CInfo& CMerchant::Get_Info()
//{
//    return *m_pInfo;
//}
//
//void CMerchant::Set_Info(CInfo* _pInfo)
//{
//    m_pInfo = _pInfo;
//}

void CMerchant::Initialize()
{
	CEntity::Initialize();
    //Set_Info(new CInfo);
    //Get_Info().Initialize();
}

void CMerchant::Release()
{
    //SAFE_DELETE(m_pInfo);
}

void CMerchant::Set_Merchant_Inven()
{


    Get_Info().Get_Inven()->ClearInven();
    Get_Info().Get_Inven()->AddItem(new CRedPotion("���� ����", 50)/*g_RedPotion*/);
	Get_Info().Get_Inven()->AddItem(new CSmall_RedPotion("���� ���� ����", 20)/*g_Small_RedPotion*/);

    //Get_Info().Get_Inven()->SetMerchantInven();
}

void CMerchant::Set_Dungeon_Merchant_Inven()
{

	Get_Info().Get_Inven()->ClearInven();
	Get_Info().Get_Inven()->AddItem(new CSword_Of_Legend("������ ��", 499)/*g_Sword_Of_Legend*/);
	Get_Info().Get_Inven()->AddItem(new CRedPotion("���� ����", 50));
	Get_Info().Get_Inven()->AddItem(new CSmall_RedPotion("���� ���� ����", 20));

	//Get_Info().Get_Inven()->SetMerchantInven();
}

void CMerchant::Open_Shop(CPlayer* _pPlayer, CInputManager* _pInputManager)
{
	while (true)
	{
		Render_Shop(_pPlayer);

		cout << "������ġ: ����" << endl;
		LINE_LINE;
		cout << "[1] ����" << endl;
		cout << "[2] �Ǹ�" << endl;
		cout << "[3] ���� ������" << endl;
		LINE_LINE;


		if (_pInputManager->Receive_Input() == INPUT_ERROR)
		{
			continue;
		}

		switch (_pInputManager->Get_Input())
		{
		case 1:
			_pPlayer->Buy_Item(this, _pInputManager);
			break;
		case 2:
			_pPlayer->Sell_Item(this, _pInputManager);
			break;
		case 3:
			//SAFE_DELETE(merchant);
			return;
		default:
			break;
		}
	}
}

void CMerchant::Render_Shop(CPlayer* _pPlayer)
{
	system("cls");

	cout << "���� ��ȭ: ";
	Set_Color(YELLOW);
	cout << _pPlayer->Get_Info().Get_Gold() << "G" << endl;
	Set_Color(GRAY);

	cout << "�÷��̾��� ";
	_pPlayer->Get_Info().Get_Inven()->PrintAll();

	LINE;

	cout << "������";
	Get_Info().Get_Inven()->PrintAll();
	cout << endl;
}
