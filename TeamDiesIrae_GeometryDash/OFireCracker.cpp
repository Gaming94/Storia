#include "stdafx.h"
#include "OFireCracker.h"


COFireCracker::COFireCracker()
{
}


COFireCracker::~COFireCracker()
{
}

void COFireCracker::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Effect/FireCracker/a3.bmp", L"a1");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"a1", L"../Image/Effect/FireCracker/a1.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"a1", L"../Image/Effect/FireCracker/a1.bmp");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;
}

void COFireCracker::LateInit()
{
}

int COFireCracker::Update()
{
	if (m_bIsDead == true)
		return DEAD_EVENT;

	return 0;
}

void COFireCracker::LateUpdate()
{
	CObj::MoveFrame();
}

void COFireCracker::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"a1"));
	GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX * 2, m_tInfo.FCY * 2, 
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
}

void COFireCracker::Release()
{
}
