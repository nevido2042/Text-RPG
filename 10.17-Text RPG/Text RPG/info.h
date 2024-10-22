#pragma once

#define NAME_LEN 32
#define MAX_INVEN 5

typedef struct tagItem
{
	char szName[NAME_LEN] = "";
	int iValue = 0; // 가치(단위: 골드)
	void PrintItem();
}ITEM;

typedef struct tagInventory
{
	ITEM itemArray[MAX_INVEN] = {};
	int iItemCount = 0;
	void AddItem(ITEM _item);
	int RemoveItem(int _iNum);
	void PrintAll();
	void ClearInven();
	void SetMerchantInven();
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
	void SetStatRandom(int _iValue = 2);
	void SetRandomPoint(int* _iStatPoint, int* _iRemainPoint, const int* _iMaxPoint);
}STAT;

typedef struct tagINFO
{
	char szName[NAME_LEN * 2] = "";
	int iDay = 1;
	STAT stat;
	STAT curStat;
	INVEN inven;
	int iGold = 0;
	
	void PrintName();
	void PrintInfo();
	void ResetStat();
}INFO;