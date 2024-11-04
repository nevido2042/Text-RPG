#pragma once
#include "info.h"
class CEntity
{
protected:
	CInfo* m_pInfo;

public:
	CEntity();
	virtual ~CEntity();
public:
	CInfo& Get_Info();
	void Set_Info(CInfo* _pInfo);

public:
	void Initialize();
	void Release();
};

