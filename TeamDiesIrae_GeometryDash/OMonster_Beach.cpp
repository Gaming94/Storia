#include "stdafx.h"

#include "COAttackRect.h"

#include "OMonster_Beach.h"

COMonster_Beach::COMonster_Beach()
{
}

COMonster_Beach::~COMonster_Beach()
{
	Release();
}

void COMonster_Beach::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Beach/Monster_Beach_Walk_L.bmp", L"Monster_Beach_Walk_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Beach/Monster_Beach_Walk_R.bmp", L"Monster_Beach_Walk_R");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Beach/Monster_Beach_Attack_L.bmp", L"Monster_Beach_Attack_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Beach/Monster_Beach_Attack_R.bmp", L"Monster_Beach_Attack_R");

	m_tInfo.FCX = 483;
	m_tInfo.FCY = 306;

	m_pFrameKey = L"Monster_Beach_Walk_R";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	m_pSpeed = 4;

	m_tStatus.Atk = 3;
	m_tStatus.Def = 0;
	m_tStatus.Cur_HP = 100;
	m_tStatus.MAX_HP = 100;

	//공격박스
	pSellect_AttackRect = AbstractFactory<COAttackRect>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_AttackRect, ObjID::OBJ_ATTACKRECT);
}

void COMonster_Beach::LateInit()
{

}

int COMonster_Beach::Update()
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

	if (m_IsLR == 1 && m_IsBattle == false)
	{
		m_Character_CurStance = Char_StanceID::WALK_L;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::WALK_R;
	}
	
	if (isAttack == true)
	{
		isMoving = false;
		if (m_IsLR == 1)
		{
			m_Character_CurStance = Char_StanceID::ATTACK_L;
		}
		else
		{
			m_Character_CurStance = Char_StanceID::ATTACK_R;
		}
	}

	if (m_IsLR == true)
	{
		pSellect_AttackRect->SetPos(m_tInfo.FX - 50, m_tInfo.FY + 10);
	}
	else
	{
		pSellect_AttackRect->SetPos(m_tInfo.FX + 50, m_tInfo.FY + 10);
	}

	// 타겟 유무 탐색
	if (pTarget == NULL || pTarget == 0)
	{
		// 타겟이 없을경우 랜덤한 패턴으로 움직입니다
		isMoving = true;
		isAttack = false;
		if (MoveSwitch == false)
			RandMove = rand() % 3;

		switch (RandMove)
		{
		case 0:
			Move_Left();
			break;

		case 1:
			Move_Right();
			break;
		}
	}
	else
	{
		// 타겟 설정시
		if (m_tInfo.FX >= pTarget->GetInfo().FX + pTarget->GetInfo().FCX + 100)
		{
			isMoving = true;
			m_IsLR = true;
			m_tInfo.FX -= m_pSpeed;
		}

		if (m_tInfo.FX <= pTarget->GetInfo().FX - pTarget->GetInfo().FCX + 100)
		{
			isMoving = true;
			m_IsLR = false;
			m_tInfo.FX += m_pSpeed;
		}

		if (m_tInfo.FY <= pTarget->GetInfo().FY + 100)
		{
			isMoving = true;
			m_tInfo.FY += m_pSpeed - 2;
		}

		if (m_tInfo.FY >= pTarget->GetInfo().FY + 100)
		{
			isMoving = true;
			m_tInfo.FY -= m_pSpeed - 2;
		}

		if (abs(m_tInfo.FX - pTarget->GetInfo().FX) <= 300)
		{
			isAttack = true;
		}
		else
		{
			isAttack = false;
		}

		if (pTarget->GetStatus().Cur_HP <= 0)
		{
			//없을시
			isMoving = true;
			isAttack = false;
			pTarget = NULL;
		}
	}

	if (SW_HitBySkillC == true)
	{
		m_tInfo.FX += 15;

		SkillCDest += 15;
	}

	if (SkillCDest >= 500)
	{
		SW_HitBySkillC = false;
		SkillCDest = 0;
	}

	//사망처리
	if (m_bIsDead == true)
	{
		pSellect_AttackRect->SetDead();
		return DEAD_EVENT;
	}

	return 0;
}

void COMonster_Beach::LateUpdate()
{
	CObj::MoveFrame();
	CObj::UpdateRect();
	SceneChange();
}

void COMonster_Beach::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 0.5, m_tInfo.FCY * 0.5,
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 128, 0));

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left + 40, m_tRect.top,
		m_tInfo.FCX - 300, 15,
		hMemDC, 0, 15,
		200, 15, RGB(98, 124, 76));

	float SubHp = float(m_tStatus.MAX_HP - m_tStatus.Cur_HP);
	float Percent = SubHp / m_tStatus.MAX_HP * 100;
	float PerPx = (m_tInfo.FCX - 300) / 100.f;
	float fValue = Percent * PerPx;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left + 40, m_tRect.top,
		m_tInfo.FCX - fValue - 300, 15,
		hMemDC, 0, 0,
		200, 15, RGB(98, 124, 76));
}

void COMonster_Beach::Release()
{
}

void COMonster_Beach::Move_Left()
{
	m_IsLR = true;

	if (MoveSwitch == false)
	{
		MoveSwitch = true;
	}
	else
	{
		m_tInfo.FX -= m_pSpeed - 2;
		Move_Dist += m_pSpeed - 2;
	}

	if (Move_Dist >= Purpose_DistX)
	{
		MoveSwitch = false;
		Move_Dist = 0;
	}
}

void COMonster_Beach::Move_Right()
{
	m_IsLR = false;

	if (MoveSwitch == false)
	{
		MoveSwitch = true;
	}
	else
	{
		m_tInfo.FX += m_pSpeed - 2;
		Move_Dist += m_pSpeed - 2;
	}

	if (Move_Dist >= Purpose_DistX)
	{
		MoveSwitch = false;
		Move_Dist = 0;
	}
}

void COMonster_Beach::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		switch (m_Character_CurStance)
		{
		case Char_StanceID::WALK_L:
			m_pFrameKey = L"Monster_Beach_Walk_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			break;

		case Char_StanceID::WALK_R:
			m_pFrameKey = L"Monster_Beach_Walk_R";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			break;

		case Char_StanceID::ATTACK_L:
			m_pFrameKey = L"Monster_Beach_Attack_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 50;
			break;

		case Char_StanceID::ATTACK_R:
			m_pFrameKey = L"Monster_Beach_Attack_R";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 50;
			break;
		}

		m_Character_PreStance = m_Character_CurStance;
	}
}
