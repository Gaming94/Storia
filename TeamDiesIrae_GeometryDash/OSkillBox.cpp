#include "stdafx.h"
#include "OSkillBox.h"


COSkillBox::COSkillBox()
{
}


COSkillBox::~COSkillBox()
{
	Release();
}

void COSkillBox::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/SkillBox/SkillBox.bmp", L"SkillBox");

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"SkillBox", L"../Image/SkillBox/SkillBox.bmp");
	m_tInfo.FCY	= CBMPMgr::GetInstance()->FindImg_SizeY(L"SkillBox", L"../Image/SkillBox/SkillBox.bmp");

}

void COSkillBox::LateInit()
{
	CObj::UpdateRect();
}

int COSkillBox::Update()
{
	return 0;
}

void COSkillBox::LateUpdate()
{
}

void COSkillBox::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"SkillBox"));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.bottom, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
}

void COSkillBox::Release()
{
}
