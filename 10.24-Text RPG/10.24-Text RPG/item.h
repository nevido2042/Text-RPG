#pragma once
#include "misc.h"

class CEntity;
class CInfo;

class CItem
{
	//enum TYPE { Potion, Head, Top, Bottom, Shoes, Weapon };

	//TYPE m_Type;
	char m_szName[NAME_LEN];
	int m_iValue; // 가치(단위: 골드)
	void(*m_pUse)(CInfo* _pUser, CInfo* _pTarget);
	void(*m_pEquip)(CEntity* _pUser);
public:
	CItem();
	CItem(const char* _szName, int _iValue = 0,
		void(*_pUse)(CInfo*, CInfo*) = nullptr,
		void(*_pEquip)(CEntity*) = nullptr);
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

	//[[nodiscard]]
	int Equip(CEntity* _pUser);

	void PrintItem();
private:
	void Refresh();
};