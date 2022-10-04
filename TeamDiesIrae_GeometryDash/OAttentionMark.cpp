#include "stdafx.h"
#include "OAttentionMark.h"


COAttentionMark::COAttentionMark()
	:UpAndDown(0), UpAndDownDest(-3), UpOrDown(0)
{
}


COAttentionMark::~COAttentionMark()
{
}

void COAttentionMark::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Attention_Mark/Attention_Mark.bmp", L"Attention_Mark");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Attention_Mark", L"../Image/Character/Attention_Mark/Attention_Mark.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Attention_Mark", L"../Image/Character/Attention_Mark/Attention_Mark.bmp");
}

void COAttentionMark::LateInit()
{
}

int COAttentionMark::Update()
{
	if (UpOrDown == false)
	{
		//false일때 올라간다
		if (UpAndDown >= UpAndDownDest)
		{
			UpAndDown-=0.5f;
		}

		if (UpAndDown == UpAndDownDest)
		{
			UpOrDown = true;
			UpAndDownDest *= -1;
		}
	}
	else
	{
		if (UpAndDown <= UpAndDownDest)
		{
			UpAndDown+=0.5f;
		}

		if (UpAndDown == UpAndDownDest)
		{
			UpOrDown = false;
			UpAndDownDest *= -1;
		}

	}

	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COAttentionMark::LateUpdate()
{
	CObj::UpdateRect();
}

void COAttentionMark::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Attention_Mark"));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top + UpAndDown, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));

	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top + UpAndDown, m_tRect.right, m_tRect.bottom + UpAndDown);
	}
}

void COAttentionMark::Release()
{
}
