#pragma once
class CInputManager
{
	int m_iInput;
public:
	CInputManager();
	~CInputManager();

public:
	int& Get_Input();
	void Set_Input(int _iInput);
public:
	void Initialize();
	void Update();
	void Release();
public:
	int Receive_Input();
private:
	int Check_Input();
};

