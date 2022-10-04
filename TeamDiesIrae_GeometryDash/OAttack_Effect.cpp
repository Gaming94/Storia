#include "stdafx.h"
#include "OAttack_Effect.h"


COAttack_Effect::COAttack_Effect()
{
	dwFrameTime = GetTickCount64();
}


COAttack_Effect::~COAttack_Effect()
{
	Release();
}

void COAttack_Effect::Init()
{
	m_CharNum = CEffectMgr::GetInstance()->GetWhatChar();

	switch (m_CharNum)
	{
	case eChar_Num::ALPONSO:
		m_tInfo.FCX = 225;
		m_tInfo.FCY = 175;
		
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 12;
		m_tFrame.iFrameScene = 0;
		m_tFrame.iFrameSceneEnd = 1;
		m_tFrame.dwFrameTime = GetTickCount64();
		m_tFrame.dwFrameSpd = 50;
		break;

	case eChar_Num::LEO:
		m_tInfo.FCX = 720;
		m_tInfo.FCY = 430;

		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 9;
		m_tFrame.iFrameScene = 0;
		m_tFrame.iFrameSceneEnd = 1;
		m_tFrame.dwFrameTime = GetTickCount64();
		m_tFrame.dwFrameSpd = 50;
		break;
	}

	CSoundMgr::GetInstance()->PlaySoundW(L"Z_Skill.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT, 0.3);
}

void COAttack_Effect::LateInit()
{
}

int COAttack_Effect::Update()
{
	if (dwFrameTime + m_tFrame.dwFrameSpd < GetTickCount64())
	{
		m_tFrame.iFrameStart++;
		dwFrameTime = GetTickCount64();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		if (m_tFrame.iFrameScene <= m_tFrame.iFrameSceneEnd)
		{
			m_tFrame.iFrameScene++;
			m_tFrame.iFrameStart = 0;
		}
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd && m_tFrame.iFrameScene >= m_tFrame.iFrameSceneEnd)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COAttack_Effect::LateUpdate()
{
}

void COAttack_Effect::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,
		hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
		m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
}

void COAttack_Effect::Release()
{
}
