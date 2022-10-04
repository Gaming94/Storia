#include "stdafx.h"
#include "OSelectMode.h"


COSelectMode::COSelectMode()
{
}


COSelectMode::~COSelectMode()
{
}

void COSelectMode::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/SelectMode/StoryMode_Color.bmp", L"StoryMode_Color");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/SelectMode/StoryMode_GrayScale.bmp", L"StoryMode_GrayScale");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/SelectMode/MiniGameMode_Color.bmp", L"MiniGameMode_Color");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/SelectMode/MiniGameMode_GrayScale.bmp", L"MiniGameMode_GrayScale");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"StoryMode_GrayScale", L"../Image/SelectMode/StoryMode_GrayScale.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"StoryMode_GrayScale", L"../Image/SelectMode/StoryMode_GrayScale.bmp");
}

void COSelectMode::LateInit()
{
}

int COSelectMode::Update()
{
	return 0;
}

void COSelectMode::LateUpdate()
{
}

void COSelectMode::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"StoryMode_GrayScale"));
	BitBlt(hdc, 0, 0, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, SRCCOPY);

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"MiniGameMode_GrayScale"));
	BitBlt(hdc, 846, 0, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, SRCCOPY);
}

void COSelectMode::Release()
{
}
