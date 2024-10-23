#include "pch.h"
#include "item.h"
#include "misc.h"

void tagItem::PrintItem()
{
	cout << szName;
	SetPrintColor(YELLOW);
	cout << " (" << iValue << "G)" << endl;
	SetPrintColor(GRAY);

}
void tagItem::Use(INFO* _pUser, INFO* _pTarget)
{
}
