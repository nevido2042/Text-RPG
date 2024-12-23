#pragma once
#include "misc.h"

class CEntity;
class CInfo;

class CItem
{
	//enum TYPE { Potion, Head, Top, Bottom, Shoes, Weapon };

	//TYPE m_Type;
protected:
	char m_szName[NAME_LEN];
	int m_iValue; // ��ġ(����: ���)
	//void(*m_pUse)(CInfo* _pUser, CInfo* _pTarget);
	//void(*m_pEquip)(CEntity* _pUser);
public:
	CItem();
	//CItem(int _iValue = 0);// ,
		//void(*_pUse)(CInfo*, CInfo*) = nullptr,
		//void(*_pEquip)(CEntity*) = nullptr);
	virtual ~CItem();
public:
	void Initialize();
	void Update();
	void Release();
public:
	char* Get_Name();
	int Get_Value();
public:
	void Set_Value(int _iValue);
	//[[nodiscard]]
	//int Equip(CEntity* _pUser);

	void PrintItem();
private:
	void Refresh();
};