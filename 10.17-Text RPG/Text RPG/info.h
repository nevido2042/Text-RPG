#pragma once

#define NAME_LEN 32
#define MAX_INVEN 10

typedef struct tagItem
{
	char szName[NAME_LEN] = "";

	void PrintItem();
}ITEM;

typedef struct tagInventory
{
	ITEM inven[MAX_INVEN] = {};

	void PrintAll();
}INVEN;

typedef struct tagStat
{
	const int iStatCount = 6;
	const int iTotalStat = iStatCount * iStatCount;

	int iHP = iStatCount;
	int iMP = iStatCount;
	int iSTR = iStatCount;
	int iDEX = iStatCount;
	int iLUK = iStatCount;
	int iINT = iStatCount;

	void RenderStat();
	void PrintALL();
	void PrintDetailStat();
	void SetStatRandom();
	void SetRandomPoint(int* _iStatPoint, int* _iRemainPoint, const int* _iMaxPoint);
}STAT;

typedef struct tagINFO
{
	char szName[NAME_LEN * 2] = "";
	int iDay = 1;
	STAT stat;
	STAT curStat;
	INVEN inven;
	
	void PrintName();
	void PrintInfo();
	void ResetStat();
}INFO;