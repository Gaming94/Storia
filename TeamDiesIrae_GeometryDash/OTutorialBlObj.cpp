#include "stdafx.h"
#include "OTutorialBlObj.h"


COTutorialBlObj::COTutorialBlObj()
{
}

COTutorialBlObj::~COTutorialBlObj()
{
}

void COTutorialBlObj::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/Tutorial/AlphaBlending_Practice3.bmp", L"AlphaBlending_Practice1");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"AlphaBlending_Practice1", L"../Image/BackGround/Tutorial/AlphaBlending_Practice3.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"AlphaBlending_Practice1", L"../Image/BackGround/Tutorial/AlphaBlending_Practice3.bmp");
}

void COTutorialBlObj::LateInit()
{
	CObj::UpdateRect();
}

int COTutorialBlObj::Update()
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

void COTutorialBlObj::LateUpdate()
{
}

void COTutorialBlObj::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"AlphaBlending_Practice1"));

	GdiAlphaBlend(hdc, m_tRect.left, m_tRect.bottom, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, blend);
}

void COTutorialBlObj::Release()
{
}
