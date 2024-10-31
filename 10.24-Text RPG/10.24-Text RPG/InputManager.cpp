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
	cout << "입력: ";
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
