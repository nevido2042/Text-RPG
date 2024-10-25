#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

CItem::CItem()//�ε��� �� �Լ� ������ �ʱ�ȭ
{
	//cout << __FUNCTION__ << endl;

	if (strcmp(m_szName, "���� ����") == SUCCESS)
	{
		extern void RecoveryHP(CInfo * _pUser, CInfo * _pTarget);
		m_pUse = &RecoveryHP;
	}
}

CItem::CItem(const char* _szName, int _iValue, void(*_pUse)(CInfo*, CInfo*))
{//������ ���� �� ���
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
		cout << "��� �� �� ���� ������ �Դϴ�." << endl;
		system("pause");
		return;
	}

	//����� �Լ��� �ּҰ�, ���̺� ���� ����, �ε����� �� �޶� ������ �� ����.
	m_pUse(_pUser, _pTarget);
}
