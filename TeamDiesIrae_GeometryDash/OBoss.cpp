#include "stdafx.h"
#include "OBoss.h"

COBoss::COBoss()
{
}

COBoss::~COBoss()
{
    Release();
}

void COBoss::Init()
{
    CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Boss/Monster_Boss_Idle_L.bmp", L"Monster_Boss_Idle_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Boss/Monster_Boss_Attack_L.bmp", L"Monster_Boss_Attack_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Boss/Monster_Boss_Walk_L.bmp", L"Monster_Boss_Walk_L");

	m_pFrameKey = L"Monster_Boss_Idle_L";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 2;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

    m_tInfo.FCX = 869;
    m_tInfo.FCY = 549;

	//스테이터스
	m_tStatus.Atk = 15;
	m_tStatus.Def = 0;
	m_tStatus.Cur_HP = 500;
	m_tStatus.MAX_HP = m_tStatus.Cur_HP;
}

int COBoss::Update()
{
	//프레임 업데이트
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameScene++;
		m_tFrame.iFrameStart = 0;
	}

	if (m_tFrame.iFrameScene >= m_tFrame.iFrameSceneEnd)
	{
		m_tFrame.iFrameScene = 0;
	}

	if (isStart == false)
	{
		if (m_tInfo.FX >= 1200)
		{
			m_Character_CurStance = Char_StanceID::WALK_L;
			m_tInfo.FX -= 2;
		}
		if (m_tInfo.FX <= 1200)
			isStart = true;
	}

	//사망
	if(m_tStatus.Cur_HP <= 0)
	{ 
		return DEAD_EVENT;
	}

    return 0;
}

void COBoss::LateUpdate()
{
    CObj::MoveFrame();
    CObj::UpdateRect();
    SceneChange();

	if (isStart == true)
	{
		//공격관련
		if (fabs(m_tInfo.FX - pTarget->GetInfo().FX) <= 500)
		{
			if (pTarget->GetStatus().Cur_HP > 0)
				m_Character_CurStance = Char_StanceID::ATTACK_L;
			else
				m_Character_CurStance = Char_StanceID::IDLE_L;
		}
		else
		{
			m_Character_CurStance = Char_StanceID::IDLE_L;
		}
	}
}

void COBoss::Render(HDC hdc)
{
    HDC hMemDC = nullptr;

	//본체
    NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
    GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 1.1, m_tInfo.FCY * 1.1,
        hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));

	//렉트표기
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left - 50, m_tRect.top, m_tRect.right - 50, m_tRect.bottom);
	}

	//체력바
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left - 50, m_tRect.top,
		m_tInfo.FCX, 15,
		hMemDC, 0, 15,
		200, 15, RGB(98, 124, 76));

	float SubHp = float(m_tStatus.MAX_HP - m_tStatus.Cur_HP);
	float Percent = SubHp / m_tStatus.MAX_HP * 100;
	float PerPx = m_tInfo.FCX / 100.f;
	float fValue = Percent * PerPx;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left - 50, m_tRect.top,
		m_tInfo.FCX - fValue, 15,
		hMemDC, 0, 0,
		200, 15, RGB(98, 124, 76));
}

void COBoss::Release()
{
}

void COBoss::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		m_tFrame.iFrameStart = 0;
		switch (m_Character_CurStance)
		{
		case Char_StanceID::IDLE_L:
			m_pFrameKey = L"Monster_Boss_Idle_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			break;

		case Char_StanceID::WALK_L:
			m_pFrameKey = L"Monster_Boss_Walk_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 60;
			break;

		case Char_StanceID::ATTACK_L:
			m_pFrameKey = L"Monster_Boss_Attack_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 80;
			break;
		}
		m_Character_PreStance = m_Character_CurStance;
	}
}
