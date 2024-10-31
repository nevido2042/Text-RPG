#include "pch.h"
#include "InputManager.h"
#include "misc.h"

CInputManager::CInputManager()
	:m_iInput(0)
{
    //m_iInput = 0;
}

CInputManager::~CInputManager()
{
}

int& CInputManager::Get_Input()
{
    return m_iInput;
}

void CInputManager::Set_Input(int _iInput)
{
    m_iInput = _iInput;
}

void CInputManager::Initialize()
{
}

void CInputManager::Update()
{
}

void CInputManager::Release()
{
}

int CInputManager::Receive_Input()
{
	cout << "�Է�: ";
	cin >> Get_Input();

	int iTemp = Check_Input();
	if (iTemp == INPUT_ERROR)
	{
		return INPUT_ERROR;
	}

	return SUCCESS;
}

int CInputManager::Check_Input()
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
