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
		cout << "사용 할 수 없는 아이템 입니다." << endl;
		system("pause");
		return;
	}

	//저장된 함수의 주소가, 세이브 했을 때랑, 로드했을 때 달라서 터지는 거 같다.
	pUse(_pUser, _pTarget);
}
