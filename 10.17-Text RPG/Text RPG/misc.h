#pragma once
//#include <Windows.h>

#define INPUT_ERROR -1
#define _ERROR -1
#define SUCCESS 0

#define NAME_LEN 32
#define MAX_INVEN 5

//����
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

// �ܼ� �ؽ�Ʈ ���� �������ִ� �Լ�
void SetPrintColor(unsigned short text);