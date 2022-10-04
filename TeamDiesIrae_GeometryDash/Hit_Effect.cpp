#include "stdafx.h"

#include "OHit_Effect.h"

#include "Hit_Effect.h"

CHit_Effect::CHit_Effect()
{
	m_tRect.left = 0;
	m_tRect.right = 0;
	m_tRect.top = 0;
	m_tRect.bottom = 0;

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;
}

CHit_Effect::~CHit_Effect()
{
	Release();
}

void CHit_Effect::Init()
{
	//그림 불러오기
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Hit_Effect/Hit_Effect2.bmp", L"Hit_Effect");

	//위치 지정
	m_tRect.left = CEffectMgr::GetInstance()->GetPosition_Left();
	m_tRect.top = CEffectMgr::GetInstance()->GetPosition_Top();
	m_tRect.right = CEffectMgr::GetInstance()->GetPosition_Right();
	m_tRect.bottom = CEffectMgr::GetInstance()->GetPosition_Bottom();

	pObj = new COHit_Effect;

	pObj->Init();

	pObj->SetImgPos(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	CObjMgr::GetInstance()->AddObject(pObj, ObjID::OBJ_EFFECT);
}

void CHit_Effect::LateInit()
{
}

int CHit_Effect::Update()
{
	return 0;
}

void CHit_Effect::LateUpdate()
{
}

void CHit_Effect::Render(HDC hdc)
{
}

void CHit_Effect::Release()
{
}
