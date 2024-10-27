#pragma once
#include "misc.h"

class CInfo;

class CItem
{
	char m_szName[NAME_LEN];
	int m_iValue; // ��ġ(����: ���)
	void(*m_pUse)(CInfo* _pUser, CInfo* _pTarget);
public:
	CItem();
	CItem(const char* _szName, int _iValue = 0, void(*_pUse)(CInfo*, CInfo*) = nullptr);
public:
	void Initialize();
	void Update();
	void Release();
public:
	char* Get_Name();
	int Get_Value();
public:
	void Set_Value(int _iValue);
public:
	void Use(CInfo* _pUser, CInfo* _pTarget);
	void PrintItem();
private:
	void Refresh();
};