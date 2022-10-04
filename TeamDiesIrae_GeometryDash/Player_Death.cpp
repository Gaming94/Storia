#include "stdafx.h"
#include "Player_Death.h"

#include "ODeath_Effect.h"


CPlayer_Death::CPlayer_Death()
{
	m_tRect.left = 0;
	m_tRect.right = 0;
	m_tRect.top = 0;
	m_tRect.bottom = 0;

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;
}


CPlayer_Death::~CPlayer_Death()
{
	Release();
}

void CPlayer_Death::Init()
{
	//그림 불러오기
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Char_Death/Char_Death.bmp", L"Char_Death");

	//위치 지정
	m_tRect.left = CEffectMgr::GetInstance()->GetPosition_Left();
	m_tRect.top = CEffectMgr::GetInstance()->GetPosition_Top();
	m_tRect.right = CEffectMgr::GetInstance()->GetPosition_Right();
	m_tRect.bottom = CEffectMgr::GetInstance()->GetPosition_Bottom();
	isitBOSS = CEffectMgr::GetInstance()->GetObjectType();

	pObj = new CODeath_Effect;

	pObj->Init();


	pObj->SetImgPos(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	pObj->SetObjectType(isitBOSS);
	CObjMgr::GetInstance()->AddObject(pObj, ObjID::OBJ_EFFECT);
}

void CPlayer_Death::LateInit()
{
}

int CPlayer_Death::Update()
{
	pObj->Update();

	return 0;
}

void CPlayer_Death::LateUpdate()
{
}

void CPlayer_Death::Render(HDC hdc)
{
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CPlayer_Death::Release()
{
}
