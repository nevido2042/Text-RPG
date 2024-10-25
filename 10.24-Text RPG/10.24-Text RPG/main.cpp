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
	//_CrtSetBreakAlloc(206); //번호로 누수 위치 확인 가능

	//col = 가로, lines = 세로
	system("mode con:cols=100 lines=40");

	SetConsoleTitle(L"Text RPG");

	CMainGame MainGame;
	MainGame.Print_MainMenu();

	//Run_TextRPG();
	
	return 0;
}

//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //그냥 위에다 호출해도 누수 확인 가능
//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); //누수 목록 다른 곳에 출력해준다는데
//_CrtDumpMemoryLeaks();//프로그램 종료 시 호출해서 누수 확인 가능
