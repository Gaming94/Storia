#include "stdafx.h"
#include "ONumbering.h"


CONumbering::CONumbering()
{
}


CONumbering::~CONumbering()
{
}

void CONumbering::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/HorseRace_Numbering/Number1.bmp", L"Number1");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/HorseRace_Numbering/Number2.bmp", L"Number2");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/HorseRace_Numbering/Number3.bmp", L"Number3");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/HorseRace_Numbering/a0.bmp", L"a0");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"a0", L"../Image/Effect/HorseRace_Numbering/a0.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"a0", L"../Image/Effect/HorseRace_Numbering/a0.bmp");

	m_tInfo.FX = WINCX + 100;
	m_tInfo.FY = (WINCY * 0.5) - 100;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 2;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;
}

void CONumbering::LateInit()
{
}

int CONumbering::Update()
{
	if (m_tInfo.FX >= -200)
	{
		m_tInfo.FX -= 30;
	}

	if (m_tInfo.FX <= -200)
	{
		m_tInfo.FX = WINCX + 200;
		Number--;
	}

	if (Number == 0)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void CONumbering::LateUpdate()
{
	CObj::MoveFrame();
}

void CONumbering::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	switch (Number)
	{
	case 1:
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Number1"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));
		break;
	case 2:
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Number2"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));
		break;
	case 3:
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Number3"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));
		break;
	}


}

void CONumbering::Release()
{
}
