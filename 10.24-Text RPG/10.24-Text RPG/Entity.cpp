#include "pch.h"
#include "Entity.h"

CEntity::CEntity()
    :m_pInfo(nullptr)
{
}

CEntity::~CEntity()
{
    Release();
}

CInfo& CEntity::Get_Info()
{
    return *m_pInfo;
}

void CEntity::Set_Info(CInfo* _pInfo)
{
    if (m_pInfo != nullptr)
    {
        PRINT_ERROR;
    }

    m_pInfo = _pInfo;
}

void CEntity::Initialize()
{
    Set_Info(new CInfo);
    Get_Info().Initialize();
}

void CEntity::Release()
{
    SAFE_DELETE(m_pInfo);
}
