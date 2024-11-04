#include "pch.h"
#include "item.h"
#include "misc.h"
#include "Entity.h"

#include "info.h"

CItem::CItem()
	:m_iValue(0)//, m_pUse(nullptr), m_pEquip(nullptr)
{
	ZeroMemory(m_szName, sizeof(m_szName));
	//m_iValue = 0;
	//m_pUse = nullptr;
}

CItem::CItem(const char* _szName, int _iValue)
	:m_iValue(_iValue)
{
	strcpy_s(m_szName, _szName);
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	Refresh();
}

void CItem::Update()
{
}

void CItem::Release()
{
}

char* CItem::Get_Name()
{
	return m_szName;
}

int CItem::Get_Value()
{
	return m_iValue;
}

void CItem::PrintItem()
{
	cout << m_szName;
	Set_Color(YELLOW);
	cout << " (" << m_iValue << "G)" << endl;
	Set_Color(GRAY);

}

void CItem::Refresh()
{
	/*if (strcmp(m_szName, "»¡°£ ¹°¾à") == SUCCESS)
	{
		extern void RecoveryHP(CInfo * _pUser, CInfo * _pTarget);
		m_iValue = 50;
		m_pUse = &RecoveryHP;
	}*/
}

void CItem::Set_Value(int _iValue)
{
	m_iValue = _iValue;
}
