#pragma once
class CStat
{
	int m_iStatCount;
	int m_iTotalStat;

	int m_iHP;
	int m_iMP;
	int m_iSTR;
	int m_iDEX;
	int m_iLUK;
	int m_iINT;

public:
	CStat();
	~CStat();

public:
	void Initialize();
	void Update();
	void Release();

public:
	int Get_HP();
	int Get_MP();
	int Get_STR();
	int Get_DEX();
	int Get_LUK();
	int Get_INT();
public:
	void Set_HP(int _iValue);
	void Set_MP(int _iValue);
	void Set_STR(int _iValue);
	void Set_DEX(int _iValue);
	void Set_LUK(int _iValue);
	void Set_INT(int _iValue);
public:
	int Roll_Dice(int iValue);
	void Add_HP(int _iValue);
	void RenderStat();
	void PrintALL();
	void PrintDetailStat();
	void SetStatRandom(int _iValue = 2);
	void SetRandomPoint(int* _iStatPoint, int* _iRemainPoint, const int* _iMaxPoint);
};