#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

CItem::CItem()//로드할 때 함수 포인터 초기화
{
	//cout << __FUNCTION__ << endl;

	if (strcmp(m_szName, "빨간 물약") == SUCCESS)
	{
		extern void RecoveryHP(CInfo * _pUser, CInfo * _pTarget);
		m_pUse = &RecoveryHP;
	}
}

CItem::CItem(const char* _szName, int _iValue, void(*_pUse)(CInfo*, CInfo*))
{//아이템 선언 시 사용
	//cout << __FUNCTION__ << endl;

	if (_szName == nullptr) return;

	strcpy_s(m_szName, _szName);
	m_iValue = _iValue;
	m_pUse = _pUse;
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
	SetPrintColor(YELLOW);
	cout << " (" << m_iValue << "G)" << endl;
	SetPrintColor(GRAY);

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
