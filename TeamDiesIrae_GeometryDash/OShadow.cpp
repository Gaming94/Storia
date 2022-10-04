#include "stdafx.h"
#include "OShadow.h"

COShadow::COShadow()
{
}

COShadow::~COShadow()
{
	Release();
}

void COShadow::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Shadow2.bmp", L"Shadow");

	m_tInfo.FCX = 80;
	m_tInfo.FCY = 10;
}

void COShadow::LateInit()
{
}

int COShadow::Update()
{
	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COShadow::LateUpdate()
{
	CObj::UpdateRect();
}

void COShadow::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Shadow"));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 128, 0));
}

void COShadow::Release()
{
}
