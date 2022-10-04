#include "stdafx.h"
#include "OHit_Effect.h"

COHit_Effect::COHit_Effect()
{
    dwFrameTime = GetTickCount64();
}

COHit_Effect::~COHit_Effect()
{
    Release();
}

void COHit_Effect::Init()
{
	m_tInfo.FCX = 400;
	m_tInfo.FCY = 400;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 2;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 30;

	CSoundMgr::GetInstance()->PlaySoundW(L"Hit_EffectSound.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT, 0.1);
}

void COHit_Effect::LateInit()
{
}

int COHit_Effect::Update()
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

void COHit_Effect::LateUpdate()
{

}

void COHit_Effect::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	if (ClearMapPos == 0)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Hit_Effect"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top + 50, m_tInfo.FCX * 0.4, m_tInfo.FCY * 0.4,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
	else if (ClearMapPos == 1)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Hit_Effect"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 0.4, m_tInfo.FCY * 0.4,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
	else if (ClearMapPos == 2)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Hit_Effect"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 0.4, m_tInfo.FCY * 0.4,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
	else if (ClearMapPos == 7)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Hit_Effect"));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top + 200, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tFrame.iFrameStart * m_tInfo.FCX, m_tFrame.iFrameScene * m_tInfo.FCY,
			m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
}

void COHit_Effect::Release()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
}
