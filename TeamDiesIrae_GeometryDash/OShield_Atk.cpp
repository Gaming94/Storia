#include "stdafx.h"
#include "OShield_Atk.h"

COShield_Atk::COShield_Atk()
	:Move_Dist(0), Dest_Dist(500)
{
}

COShield_Atk::~COShield_Atk()
{
	Release();
}

void COShield_Atk::Init()
{
	m_tInfo.FCX = 413;
	m_tInfo.FCY = 223;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	CSoundMgr::GetInstance()->PlaySoundW(L"Shiled_Attack.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT, 0.1);
}

void COShield_Atk::LateInit()
{
}

int COShield_Atk::Update()
{
	if (m_IsLR == true)
	{
		//방향에 맞게 돌진
		if (Move_Dist <= Dest_Dist)
		{
			m_tInfo.FX += 15;
			Move_Dist += 10;
		}
	}
	else
	{
		if (Move_Dist <= Dest_Dist)
		{
			m_tInfo.FX -= 15;
			Move_Dist += 10;
		}
	}

	//소멸
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COShield_Atk::LateUpdate()
{
	CObj::UpdateRect();
	CObj::MoveFrame();
}

void COShield_Atk::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Shield_Atk_R"));
	GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY,
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 128, 0));
}

void COShield_Atk::Release()
{
}
