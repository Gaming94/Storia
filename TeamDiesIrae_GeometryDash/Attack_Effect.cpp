#include "stdafx.h"
#include "Attack_Effect.h"

#include "OAttack_Effect.h"


CAttack_Effect::CAttack_Effect()
{
	m_tRect.left = 0;
	m_tRect.right = 0;
	m_tRect.top = 0;
	m_tRect.bottom = 0;

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_CharNum = 0;
}


CAttack_Effect::~CAttack_Effect()
{
	Release();
}

void CAttack_Effect::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Char_Attack_Effect/Alponso_Attack_Effect.bmp", L"Alponso_Attack_Effect");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/Char_Attack_Effect/Leo_Attack_Effect_Reverse.bmp", L"Leo_Attack_Effect");

	m_tRect.left = CEffectMgr::GetInstance()->GetPosition_Left();
	m_tRect.top = CEffectMgr::GetInstance()->GetPosition_Top();
	m_tRect.right = CEffectMgr::GetInstance()->GetPosition_Right();
	m_tRect.bottom = CEffectMgr::GetInstance()->GetPosition_Bottom(); 

	m_CharNum = CEffectMgr::GetInstance()->GetWhatChar();

	pObj = new COAttack_Effect;

	pObj->Init();

	switch (m_CharNum)
	{
	case eChar_Num::ALPONSO:
		dynamic_cast<COAttack_Effect*>(pObj)->SetFrame(L"Alponso_Attack_Effect");
		break;
	case eChar_Num::LEO:
		dynamic_cast<COAttack_Effect*>(pObj)->SetFrame(L"Leo_Attack_Effect");
		break;
	default:
		break;
	}
	pObj->SetImgPos(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	CObjMgr::GetInstance()->AddObject(pObj, ObjID::OBJ_EFFECT);
}

void CAttack_Effect::LateInit()
{
}

int CAttack_Effect::Update()
{
	pObj->Update();

	return 0;
}

void CAttack_Effect::LateUpdate()
{
}

void CAttack_Effect::Render(HDC hdc)
{
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CAttack_Effect::Release()
{
}
