#include "stdafx.h"

#include "OShield_Atk.h"

#include "Shiled_Atk.h"

EShiled_Atk::EShiled_Atk()
{
	m_tRect.left = 0;
	m_tRect.right = 0;
	m_tRect.top = 0;
	m_tRect.bottom = 0;

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;
}

EShiled_Atk::~EShiled_Atk()
{
	Release();
}

void EShiled_Atk::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Shield_Atk/Shield_Atk_L.bmp", L"Shield_Atk_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Shield_Atk/Shield_Atk_R.bmp", L"Shield_Atk_R");

	m_tRect.left = CEffectMgr::GetInstance()->GetPosition_Left();
	m_tRect.top = CEffectMgr::GetInstance()->GetPosition_Top();
	m_tRect.right = CEffectMgr::GetInstance()->GetPosition_Right();
	m_tRect.bottom = CEffectMgr::GetInstance()->GetPosition_Bottom();
	
	pObj = new COShield_Atk;

	pObj->Init();

	pObj->SetImgPos(m_tRect.left - 50, m_tRect.top - 30);
	//pObj->SetImgPos(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	CObjMgr::GetInstance()->AddObject(pObj, ObjID::OBJ_EFFECT);
}

void EShiled_Atk::LateInit()
{
}

int EShiled_Atk::Update()
{
	return 0;
}

void EShiled_Atk::LateUpdate()
{
}

void EShiled_Atk::Render(HDC hdc)
{
}

void EShiled_Atk::Release()
{
}
