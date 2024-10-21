#include"misc.h"
#include<Windows.h>

void SetPrintColor(unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}
