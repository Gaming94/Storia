#include "stdafx.h"
#include "OTutorialBlObj2.h"


COTutorialBlObj2::COTutorialBlObj2()
{
}


COTutorialBlObj2::~COTutorialBlObj2()
{
}

void COTutorialBlObj2::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/Tutorial/AlphaBlending_Practice.bmp", L"AlphaBlending_Practice2");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"AlphaBlending_Practice2", L"../Image/BackGround/Tutorial/AlphaBlending_Practice.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"AlphaBlending_Practice2", L"../Image/BackGround/Tutorial/AlphaBlending_Practice.bmp");
}

void COTutorialBlObj2::LateInit()
{
	CObj::UpdateRect();
}

int COTutorialBlObj2::Update()
{
	if (BlendOnOff == true)
	{
		blend.SourceConstantAlpha = 100;
	}
	else
	{
		blend.SourceConstantAlpha = 254;
	}

	return 0;
}

void COTutorialBlObj2::LateUpdate()
{
}

void COTutorialBlObj2::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"AlphaBlending_Practice2"));

	GdiAlphaBlend(hdc, m_tRect.left, m_tRect.bottom, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, blend);
}

void COTutorialBlObj2::Release()
{
}
