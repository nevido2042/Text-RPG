#pragma once
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