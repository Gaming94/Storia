#include "stdafx.h"

#include "OShadow.h"

#include "OCookie.h"


COCookie::COCookie()
{
}


COCookie::~COCookie()
{
}

void COCookie::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		switch (m_Character_CurStance)
		{
		case Char_StanceID::IDLE_R:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"NPC_IDLE_R";
			break;

		case Char_StanceID::IDLE_L:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"NPC_IDLE_L";
			break;
		}
		m_Character_PreStance = m_Character_CurStance;
	}
}

void COCookie::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/NPC/NPC_IDLE_L.bmp", L"NPC_IDLE_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/NPC/NPC_IDLE_R.bmp", L"NPC_IDLE_R");

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_pFrameKey = L"NPC_IDLE_L";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"NPC_IDLE_L", L"../Image/Character/NPC/NPC_IDLE_L.bmp") / (m_tFrame.iFrameEnd + 1);
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"NPC_IDLE_L", L"../Image/Character/NPC/NPC_IDLE_L.bmp") / 2;

	pSellect_Shadow = AbstractFactory<COShadow>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Shadow, ObjID::OBJ_SHADOW);
}

void COCookie::LateInit()
{

}

int COCookie::Update()
{
	if (m_tInfo.FX >= pTarget->GetInfo().FX)
	{
		m_IsLR = true;
	}
	else
	{
		m_IsLR = false;
	}


	return 0;
}

void COCookie::LateUpdate()
{
	CObj::UpdateRect();
	CObj::MoveFrame();
	SceneChange();

	if (m_IsLR == true)
	{
		pSellect_Shadow->SetPos(m_tRect.left + 100, m_tRect.bottom - 65);
	}
	else
	{
		pSellect_Shadow->SetPos(m_tRect.left + 50, m_tRect.bottom - 65);
	}

	if (m_IsLR == true)
	{
		m_Character_CurStance = Char_StanceID::IDLE_L;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::IDLE_R;
	}
}

void COCookie::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 0.8, m_tInfo.FCY * 0.8,
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));

	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void COCookie::Release()
{
}
