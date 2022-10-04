#include "stdafx.h"
#include "DamageFont.h"

#include "ODamageFont.h"

CDamageFont::CDamageFont()
{
	m_tRect.left = 0;
	m_tRect.right = 0;
	m_tRect.top = 0;
	m_tRect.bottom = 0;

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;
}

CDamageFont::~CDamageFont()
{
	Release();
}

void CDamageFont::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Damage/Damage_Fontblack.bmp", L"Damage_Fontblack");

	m_tRect.left = CEffectMgr::GetInstance()->GetPosition_Left();
	m_tRect.top = CEffectMgr::GetInstance()->GetPosition_Top();
	m_tRect.right = CEffectMgr::GetInstance()->GetPosition_Right();
	m_tRect.bottom = CEffectMgr::GetInstance()->GetPosition_Bottom();

	pObj = new CODamageFont;

	pObj->Init();

	pObj->SetImgPos(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	pObj->LateInit();

	CObjMgr::GetInstance()->AddObject(pObj, ObjID::OBJ_EFFECT);
}

void CDamageFont::LateInit()
{
}

int CDamageFont::Update()
{
	pObj->Update();

	return 0;
}

void CDamageFont::LateUpdate()
{
}

void CDamageFont::Render(HDC hdc)
{
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CDamageFont::Release()
{
}
