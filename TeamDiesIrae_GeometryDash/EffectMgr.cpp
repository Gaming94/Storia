#include "stdafx.h"
#include "Effect.h"

#include "Player_Death.h"
#include "Attack_Effect.h"
#include "Hit_Effect.h"
#include "Shiled_Atk.h"
//#include "DamageFont.h"

#include "EffectMgr.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
	:m_CharNum(0)
{
}


CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::SetWhatChar(int _CharNum)
{
	m_CharNum = _CharNum;
}

void CEffectMgr::Init()
{
	//재작성 필요
}

int CEffectMgr::Update()
{
	if (m_pEffect == nullptr)
	{
		return 1;
	}
	m_pEffect->Update();
	return 0;
}

void CEffectMgr::LateUpdate()
{
	if (m_pEffect == nullptr)
	{
		return;
	}
	m_pEffect->LateUpdate();
}

void CEffectMgr::Render(HDC hdc)
{
	if (m_pEffect == nullptr)
	{
		return;
	}
	m_pEffect->Render(hdc);
}

void CEffectMgr::Release()
{
	if (m_pEffect == nullptr)
	{
		return;
	}
	else
	{
		SafeDelete(m_pEffect);
	}
}

void CEffectMgr::Effect_Change(EFFECTID eID)
{
	m_eCurEffect = eID;

	SafeDelete(m_pEffect);
	
	switch (m_eCurEffect)
	{
	case CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH:
		m_pEffect = new CPlayer_Death;
		break;
	case CEffectMgr::EFFECTID::EFFECT_PLAYERATTACK:
		m_pEffect = new CAttack_Effect;
		break;
	case CEffectMgr::EFFECTID::EFFECT_PLAYER_CSKILL:
		m_pEffect = new EShiled_Atk;
		break;
	case CEffectMgr::EFFECTID::EFFECT_HIT:
		m_pEffect = new CHit_Effect;
		break;
	}

	if (m_pEffect == nullptr)
	{
		return;
	}

	m_pEffect->Init();
	m_ePreEffect = m_eCurEffect;
}
