#include "pch.h"
#include "TextRPG.h"
#include "MainGame.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(206); //��ȣ�� ���� ��ġ Ȯ�� ����

	//col = ����, lines = ����
	system("mode con:cols=100 lines=40");

	SetConsoleTitle(L"Text RPG");

	CMainGame MainGame;
	MainGame.Print_MainMenu();

	//Run_TextRPG();
	
	return 0;
}

//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�׳� ������ ȣ���ص� ���� Ȯ�� ����
//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); //���� ��� �ٸ� ���� ������شٴµ�
//_CrtDumpMemoryLeaks();//���α׷� ���� �� ȣ���ؼ� ���� Ȯ�� ����
