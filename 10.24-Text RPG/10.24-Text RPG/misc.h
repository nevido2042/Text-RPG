#pragma once

using namespace std;

#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}

#define INPUT_ERROR -1
#define _ERROR -1
#define CANCLE -1
#define SUCCESS 0

#define NAME_LEN 32
#define MAX_INVEN 5

#define LINE_LINE cout << "===========================" << endl
#define LINE cout << "---------------------------" << endl


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
void Set_Color(unsigned short text);