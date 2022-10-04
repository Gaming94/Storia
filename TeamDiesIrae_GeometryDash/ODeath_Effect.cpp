#include "stdafx.h"
#include "ODeath_Effect.h"

CODeath_Effect::CODeath_Effect()
{
    dwFrameTime = GetTickCount64();
}

CODeath_Effect::~CODeath_Effect()
{
    Release();
}

void CODeath_Effect::Init()
{
	m_tInfo.FCX = 155;
	m_tInfo.FCY = 155;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 2;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 50;

	CSoundMgr::GetInstance()->PlaySoundW(L"Death_EffectSound.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT, 0.3);
}

void CODeath_Effect::LateInit()
{
}

int CODeath_Effect::Update()
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

void CODeath_Effect::LateUpdate()
{
}

void CODeath_Effect::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	if (isitBoss == false)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Char_Death"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
	else
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Char_Death"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 4, m_tInfo.FCY * 4,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
}

void CODeath_Effect::Release()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
}
