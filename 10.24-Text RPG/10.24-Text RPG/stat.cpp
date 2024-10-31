#include "pch.h"
#include "stat.h"

//extern int RollDice(int iMaxPoint);

CStat::CStat()
	:m_iStatCount(0), m_iTotalStat(0),
	m_iHP(0), m_iMP(0), 
	m_iSTR(0), m_iDEX(0), m_iLUK(0), m_iINT(0)
{
	/*m_iStatCount = 0;
	m_iTotalStat = 0;

	m_iMP = 0;
	m_iSTR = 0;
	m_iHP = 0;
	m_iDEX = 0;
	m_iLUK = 0;
	m_iINT = 0;*/
}

CStat::~CStat()
{
}

void CStat::Initialize()
{
	m_iStatCount = 6;
	m_iTotalStat = m_iStatCount * m_iStatCount;

	m_iMP = m_iStatCount;
	m_iSTR = m_iStatCount;
	m_iHP = m_iStatCount;
	m_iDEX = m_iStatCount;
	m_iLUK = m_iStatCount;
	m_iINT = m_iStatCount;
}

void CStat::Update()
{
}

void CStat::Release()
{
}

int CStat::Get_HP() const
{
	return m_iHP;
}

int CStat::Get_MP()
{
	return m_iMP;
}

int CStat::Get_STR()
{
	return m_iSTR;
}

int CStat::Get_DEX()
{
	return m_iDEX;
}

int CStat::Get_LUK()
{
	return m_iLUK;
}

int CStat::Get_INT()
{
	return m_iINT;
}

void CStat::Set_HP(int _iValue)
{
	m_iHP = _iValue;
}

void CStat::Set_MP(int _iValue)
{
	m_iMP = _iValue;
}

void CStat::Set_STR(int _iValue)
{
	m_iSTR = _iValue;
}

void CStat::Set_DEX(int _iValue)
{
	m_iDEX = _iValue;
}

void CStat::Set_LUK(int _iValue)
{
	m_iLUK = _iValue;
}

void CStat::Set_INT(int _iValue)
{
	m_iINT = _iValue;
}

int CStat::Roll_Dice(int iValue)
{
	if (iValue == 0)
		return 0;

	return rand() % iValue + 1;
}

void CStat::Add_HP(int _iValue)
{
	m_iHP += _iValue;
}

void CStat::RenderStat()
{
	cout << "체력: ";
	for (int i = 0; i < m_iHP; ++i)
	{
		cout << "■";
	}
	cout << endl;

	cout << "마나: ";
	for (int i = 0; i < m_iMP; ++i)
	{
		cout << "★";
	}
	cout << endl;

	cout << "공격력: ";
	for (int i = 0; i < m_iSTR; ++i)
	{
		cout << "†";
	}
	cout << endl;
}

void CStat::PrintALL() const
{
	cout << "HP: " << m_iHP << endl;
	cout << "MP: " << m_iMP << endl;
	cout << "STR: " << m_iSTR << endl;
	cout << "DEX: " << m_iDEX << endl;
	cout << "LUK: " << m_iLUK << endl;
	cout << "INT: " << m_iINT << endl;
}

void CStat::PrintDetailStat() const
{
	cout << "STR: " << m_iSTR << endl;
	cout << "DEX: " << m_iDEX << endl;
	cout << "LUK: " << m_iLUK << endl;
	cout << "INT: " << m_iINT << endl;
}

void CStat::SetStatRandom(int _iValue)
{
	const int iMaxPoint = m_iStatCount * _iValue;
	Set_HP(Roll_Dice(iMaxPoint));
	Set_MP(Roll_Dice(iMaxPoint));
	Set_STR(Roll_Dice(iMaxPoint));
	Set_DEX(Roll_Dice(iMaxPoint));
	Set_LUK(Roll_Dice(iMaxPoint));
	Set_INT(Roll_Dice(iMaxPoint));
}

void CStat::SetRandomPoint(int* _iStatPoint, int* _iRemainPoint, const int* _iMaxPoint)
{
	int iRandomPoint = rand() % *_iMaxPoint + 1;
	if (*_iRemainPoint - iRandomPoint <= 0)
	{
		*_iStatPoint = *_iRemainPoint;
		*_iRemainPoint = 0;
		return;
	}

	*_iStatPoint = iRandomPoint;
	*_iRemainPoint -= iRandomPoint;
}