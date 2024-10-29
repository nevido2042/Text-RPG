#include "pch.h"
#include "Merchant.h"
#include "Player.h"

CMerchant::CMerchant()
{
    m_pInfo = nullptr;
}

CMerchant::~CMerchant()
{
    Release();
}

CInfo& CMerchant::Get_Info()
{
    return *m_pInfo;
}

void CMerchant::Set_Info(CInfo* _pInfo)
{
    m_pInfo = _pInfo;
}

void CMerchant::Initialize()
{
    Set_Info(new CInfo);
    Get_Info().Initialize();
}

void CMerchant::Release()
{
    SAFE_DELETE(m_pInfo);
}

void CMerchant::Set_Merchant_Inven()
{
    extern CItem redPotion;
    Get_Info().Get_Inven()->ClearInven();
    Get_Info().Get_Inven()->AddItem(redPotion);
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
		cout << "[3] ����ó�� ���ư���" << endl;
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
