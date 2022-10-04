#include "stdafx.h"
#include "OBckGroundEffect.h"

COBckGroundEffect::COBckGroundEffect()
{
}

COBckGroundEffect::~COBckGroundEffect()
{
	Release();
}

void COBckGroundEffect::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/Raven/Raven_BackGroundEffect.bmp", L"Raven_BackGroundEffect");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Raven_BackGroundEffect", L"../Image/BackGround/Raven/Raven_BackGroundEffect.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Raven_BackGroundEffect", L"../Image/BackGround/Raven/Raven_BackGroundEffect.bmp");
}

void COBckGroundEffect::LateInit()
{
	CObj::UpdateRect();
}

int COBckGroundEffect::Update()
{
	m_tInfo.FX += 2;

	if (m_tRect.left >= WINCX)
	{
		m_tInfo.FX = -900;
	}

	return 0;
}

void COBckGroundEffect::LateUpdate()
{
	CObj::UpdateRect();
}

void COBckGroundEffect::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Raven_BackGroundEffect"));

	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,
		hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));

}

void COBckGroundEffect::Release()
{
}
