#include "stdafx.h"
#include "ODamageFont.h"

CODamageFont::CODamageFont()
    :MoveDst(0), PurPoseDst(15)
{
}

CODamageFont::~CODamageFont()
{
    Release();
}

void CODamageFont::Init()
{
    m_tInfo.FCX = 50;
    m_tInfo.FCY = 60;
}

void CODamageFont::LateInit()
{
    Damage = rand() % 5 + 4;
    Damage = 5;
}

int CODamageFont::Update()
{
    //if (MoveDst <= PurPoseDst)
    //{
    //    m_tInfo.FX += 20;
    //    m_tInfo.FY -= 100;
    //
    //    MoveDst++;
    //}
    
    //if (MoveDst >= PurPoseDst)
    //{
    //    return DEAD_EVENT;
    //}

    return 0;
}

void CODamageFont::LateUpdate()
{
}

void CODamageFont::Render(HDC hdc)
{
    HDC hMemDC = nullptr;

    NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Damage_Fontblack"));
    GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,
        hMemDC, m_tInfo.FCX * Damage, 0,
        m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));
}

void CODamageFont::Release()
{
}
