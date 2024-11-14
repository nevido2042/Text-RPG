#pragma once
#include "item.h"

class CEquipment_Item : public CItem
{
	public:
		virtual int Equip(CEntity* _pUser) = 0;
		virtual int Unequip(CEntity* _pUser) = 0;
};

