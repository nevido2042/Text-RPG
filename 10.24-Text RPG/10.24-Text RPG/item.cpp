#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

CItem::CItem()
{
	ZeroMemory(m_szName, sizeof(m_szName));
	m_iValue = 0;
	m_pUse = nullptr;
}

CItem::CItem(const char* _szName, int _iValue, void(*_pUse)(CInfo*, CInfo*))
{
	CItem();

	if (_szName == nullptr) return;

	strcpy_s(m_szName, _szName);
	m_iValue = _iValue;
	m_pUse = _pUse;
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
	if (strcmp(m_szName, "빨간 물약") == SUCCESS)
	{
		extern void RecoveryHP(CInfo * _pUser, CInfo * _pTarget);
		m_iValue = 50;
		m_pUse = &RecoveryHP;
	}
}

void CItem::Set_Value(int _iValue)
{
	m_iValue = _iValue;
}

void CItem::Use(CInfo* _pUser, CInfo* _pTarget)
{
	if (m_pUse == nullptr)
	{
		cout << "사용 할 수 없는 아이템 입니다." << endl;
		system("pause");
		return;
	}

	//저장된 함수의 주소가, 세이브 했을 때랑, 로드했을 때 달라서 터지는 거 같다.
	m_pUse(_pUser, _pTarget);
}
