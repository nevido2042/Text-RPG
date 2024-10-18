#pragma once

#define NAME_LEN 8

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

	void PrintName();
	void PrintInfo();
	void ResetStat();
}INFO;