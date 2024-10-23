#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

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

	pUse(_pUser, _pTarget);
}
