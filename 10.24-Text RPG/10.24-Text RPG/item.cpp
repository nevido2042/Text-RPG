#include "pch.h"
#include "item.h"
#include "misc.h"

#include "info.h"

tagItem::tagItem()//로드할 때 함수 포인터 초기화
{
	//cout << __FUNCTION__ << endl;

	if (strcmp(szName, "빨간 물약") == SUCCESS)
	{
		extern void RecoveryHP(INFO * _pUser, INFO * _pTarget);
		pUse = &RecoveryHP;
	}
}

tagItem::tagItem(const char* _szName, int _iValue, void(*_pUse)(INFO*, INFO*))
{//아이템 선언 시 사용
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
		cout << "사용 할 수 없는 아이템 입니다." << endl;
		system("pause");
		return;
	}

	//저장된 함수의 주소가, 세이브 했을 때랑, 로드했을 때 달라서 터지는 거 같다.
	pUse(_pUser, _pTarget);
}
