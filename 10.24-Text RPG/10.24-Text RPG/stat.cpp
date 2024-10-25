#include "pch.h"
#include "stat.h"

extern int RollDice(int iMaxPoint);

int CStat::Get_HP()
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

void CStat::Add_HP(int _iValue)
{
	m_iHP += _iValue;
}

void CStat::RenderStat()
{
	//cout << "====================" << endl;
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

	//cout << "====================" << endl;
}

void CStat::PrintALL()
{
	//cout << "====================" << endl;
	cout << "HP: " << m_iHP << endl;
	cout << "MP: " << m_iMP << endl;
	cout << "STR: " << m_iSTR << endl;
	cout << "DEX: " << m_iDEX << endl;
	cout << "LUK: " << m_iLUK << endl;
	cout << "INT: " << m_iINT << endl;
	//cout << "====================" << endl;
	//system("pause");
}

void CStat::PrintDetailStat()
{
	cout << "STR: " << m_iSTR << endl;
	cout << "DEX: " << m_iDEX << endl;
	cout << "LUK: " << m_iLUK << endl;
	cout << "INT: " << m_iINT << endl;
}

void CStat::SetStatRandom(int _iValue)
{
	const int iMaxPoint = m_iStatCount * _iValue;
	Set_HP(RollDice(iMaxPoint));
	Set_MP(RollDice(iMaxPoint));
	Set_STR(RollDice(iMaxPoint));
	Set_DEX(RollDice(iMaxPoint));
	Set_LUK(RollDice(iMaxPoint));
	Set_INT(RollDice(iMaxPoint));

	//const int iMaxPoint = iStatCount * _iValue;
	//int iRemainPoint = iTotalStat;

	//SetRandomPoint(&iHP, &iRemainPoint, &iMaxPoint);
	//SetRandomPoint(&iMP, &iRemainPoint, &iMaxPoint);
	//SetRandomPoint(&iSTR, &iRemainPoint, &iMaxPoint);
	//SetRandomPoint(&iDEX, &iRemainPoint, &iMaxPoint);
	//SetRandomPoint(&iLUK, &iRemainPoint, &iMaxPoint);
	////iINT = iRemainPoint;
	//SetRandomPoint(&iINT, &iRemainPoint, &iMaxPoint);
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