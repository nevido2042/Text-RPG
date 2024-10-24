#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

tagItem::tagItem()//�ε��� �� �Լ� ������ �ʱ�ȭ
{
	//cout << __FUNCTION__ << endl;

	if (strcmp(szName, "���� ����") == SUCCESS)
	{
		extern void RecoveryHP(INFO * _pUser, INFO * _pTarget);
		pUse = &RecoveryHP;
	}
}

tagItem::tagItem(const char* _szName, int _iValue, void(*_pUse)(INFO*, INFO*))
{//������ ���� �� ���
	//cout << __FUNCTION__ << endl;

	if (_szName == nullptr) return;

	strcpy_s(szName, _szName);
	iValue = _iValue;
	pUse = _pUse;
}

void tagItem::PrintItem()
{
	cout << szName;
	SetPrintColor(YELLOW);
	cout << " (" << iValue << "G)" << endl;
	SetPrintColor(GRAY);

}

void tagItem::Use(INFO* _pUser, INFO* _pTarget)
{
	if (pUse == nullptr)
	{
		cout << "��� �� �� ���� ������ �Դϴ�." << endl;
		system("pause");
		return;
	}

	//����� �Լ��� �ּҰ�, ���̺� ���� ����, �ε����� �� �޶� ������ �� ����.
	pUse(_pUser, _pTarget);
}
