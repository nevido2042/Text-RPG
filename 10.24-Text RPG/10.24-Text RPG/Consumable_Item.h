#pragma once
#include "item.h"
class CConsumable_Item :public CItem
{
public:
	virtual int Use(CEntity* _pUser, CEntity* _pTarget) = 0;
};

