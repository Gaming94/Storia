#include "stdafx.h"
#include "OLeo_Illust.h"


COLeo_Illust::COLeo_Illust()
{
}


COLeo_Illust::~COLeo_Illust()
{
	Release();
}

void COLeo_Illust::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_illust.bmp", L"Leo_illust");

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Leo_illust", L"../Image/Character/Leo/Leo_illust.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Leo_illust", L"../Image/Character/Leo/Leo_illust.bmp");
}

void COLeo_Illust::LateInit()
{
}

int COLeo_Illust::Update()
{
	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COLeo_Illust::LateUpdate()
{
}

void COLeo_Illust::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	
	if (isTeller == true)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Leo_illust"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}
}

void COLeo_Illust::Release()
{
}
