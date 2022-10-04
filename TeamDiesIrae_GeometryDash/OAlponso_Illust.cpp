#include "stdafx.h"
#include "OAlponso_Illust.h"


COAlponso_Illust::COAlponso_Illust()
{
}


COAlponso_Illust::~COAlponso_Illust()
{
	Release();
}

void COAlponso_Illust::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Char_Illust/Alponso_illust_L.bmp", L"Alponso_illust_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Char_Illust/Alponso_illust_R.bmp", L"Alponso_illust_R");

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Alponso_illust_L", L"../Image/Character/Alponso/Char_Illust/Alponso_illust_L.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Alponso_illust_L", L"../Image/Character/Alponso/Char_Illust/Alponso_illust_L.bmp");
}

void COAlponso_Illust::LateInit()
{
}

int COAlponso_Illust::Update()
{
	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}

	if (isPuzzle == true)
	{
		m_tPuzzleInfo.FCX = 215;
		m_tPuzzleInfo.FCY = 268;
	}

	return 0;
}

void COAlponso_Illust::LateUpdate()
{
	CObj::UpdateRect();
}

void COAlponso_Illust::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	if (isTeller == true)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Alponso_illust_L"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
	}

	if (isPuzzle == true)
	{
		if (m_CntX == 2 && m_CntY == 2)
		{
			
		}
		else
		{
			NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Alponso_illust_L"));
			BitBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tPuzzleInfo.FCX, m_tPuzzleInfo.FCY,
				hMemDC, m_tPuzzleInfo.FX + m_tPuzzleInfo.FCX * m_CntX, m_tPuzzleInfo.FY + m_tPuzzleInfo.FCY * m_CntY, SRCCOPY);
		}


		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Alponso_illust_L"));
		GdiTransparentBlt(hdc, 0, 0, m_tInfo.FCX * 0.5, m_tInfo.FCY * 0.5,
			hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));
	}
}

void COAlponso_Illust::Release()
{
}
