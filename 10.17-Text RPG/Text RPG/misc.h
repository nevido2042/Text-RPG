#pragma once
//#include <Windows.h>

#define INPUT_ERROR -1
#define _ERROR -1
#define SUCCESS 0

#define NAME_LEN 32
#define MAX_INVEN 5

//색상
enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DAKR_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

// 콘솔 텍스트 색상 변경해주는 함수
void SetPrintColor(unsigned short text);