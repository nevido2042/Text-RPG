#pragma once
#include "item.h"
class CConsumable_Item :public CItem
{
public:
	CConsumable_Item();
public:
	virtual int Use(CEntity* _pUser, CEntity* _pTarget) = 0;
};

