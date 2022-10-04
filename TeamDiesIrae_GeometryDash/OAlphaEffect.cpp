#include "stdafx.h"
#include "OAlphaEffect.h"


COAlphaEffect::COAlphaEffect()
{
}


COAlphaEffect::~COAlphaEffect()
{
	Release();
}

void COAlphaEffect::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/BackGround_Black.bmp", L"BackGround_Black");
}

void COAlphaEffect::LateInit()
{
}

int COAlphaEffect::Update()
{
	if (isFadeinout == false)
	{
		//fade_in
		blend.SourceConstantAlpha = blendCnt;
		if (blendCnt >= 0)
		{
			blendCnt -= 5;
		}
	}
	else
	{
		//fade_out
		blend.SourceConstantAlpha = RblendCnt;
		if (RblendCnt <= 255)
		{
			RblendCnt += 5;
		}
	}

	if (m_bIsDead)
		return DEAD_EVENT;

	return 0;
}

void COAlphaEffect::LateUpdate()
{
}

void COAlphaEffect::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"BackGround_Black"));
	GdiAlphaBlend(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, blend);
}

void COAlphaEffect::Release()
{
}
