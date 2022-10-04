#include "stdafx.h"
#include "OMonster_Practice.h"

#include "COAttackRect.h"


COMonster_Practice::COMonster_Practice()
	:MoveSwitch(0)
{
}


COMonster_Practice::~COMonster_Practice()
{
	Release();
}

void COMonster_Practice::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Ground/Monster_Ground_Walk_L.bmp", L"Monster_Ground_Walk_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Ground/Monster_Ground_Walk_R.bmp", L"Monster_Ground_Walk_R");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Ground/Monster_Ground_Attack_L.bmp", L"Monster_Ground_Attack_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Monster/Monster_Ground/Monster_Ground_Attack_R.bmp", L"Monster_Ground_Attack_R");

	m_pFrameKey = L"Monster_Ground_Walk_L";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	m_Character_CurStance = Char_StanceID::WALK_L;
	m_Character_PreStance = m_Character_CurStance;

	m_tInfo.FCX = 171;
	m_tInfo.FCY = 136;

	m_pSpeed = 4;

	m_tStatus.Atk = 4;
	m_tStatus.Def = 0;
	m_tStatus.Cur_HP = 100;
	m_tStatus.MAX_HP = 100;

	//공격박스
	pSellect_AttackRect = AbstractFactory<COAttackRect>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_AttackRect, ObjID::OBJ_ATTACKRECT);
}

void COMonster_Practice::LateInit()
{
}

int COMonster_Practice::Update()
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

	//타겟 유무
	if (pTarget == NULL || pTarget == 0)
	{
		//없을시
		isMoving = true;
		isAttack = false;
		if (MoveSwitch == false)
			RandMove = rand() % 3;

		switch (RandMove)
		{
		case 0:
			//좌로 이동
			Move_Left();
			break;

		case 1:
			//우로 이동
			Move_Right();
			break;
		}
	}
	else
	{
		//타겟 설정시
		if (m_tInfo.FX >= pTarget->GetInfo().FX + pTarget->GetInfo().FCX - 50)
		{
			isMoving = true;
			m_IsLR = true;
			m_tInfo.FX -= m_pSpeed;
		}

		if (m_tInfo.FX <= pTarget->GetInfo().FX - pTarget->GetInfo().FCX + 50)
		{
			isMoving = true;
			m_IsLR = false;
			m_tInfo.FX += m_pSpeed;
		}

		if (m_tInfo.FY <= pTarget->GetInfo().FY + 50)
		{
			isMoving = true;
			m_tInfo.FY += m_pSpeed - 2;
		}

		if (m_tInfo.FY >= pTarget->GetInfo().FY + 50)
		{
			isMoving = true;
			m_tInfo.FY -= m_pSpeed - 2;
		}

		if (abs(m_tInfo.FX - pTarget->GetInfo().FX) <= 150)
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

	if (m_bIsDead == true)
	{
		pSellect_AttackRect->SetDead();
		return DEAD_EVENT;
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

	return 0;
}

void COMonster_Practice::LateUpdate()
{
	CObj::MoveFrame();
	CObj::UpdateRect();
	SceneChange();
}

void COMonster_Practice::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX * 0.75, m_tInfo.FCY * 0.75,
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(255, 255, 255));

	//렉트표기
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

	//체력바 연습
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top,
		m_tInfo.FCX, 15,
		hMemDC, 0, 15,
		200, 15, RGB(98, 124, 76));

	float SubHp = float(m_tStatus.MAX_HP - m_tStatus.Cur_HP);
	float Percent = SubHp / m_tStatus.MAX_HP * 100;
	float PerPx = m_tInfo.FCX / 100.f;
	float fValue = Percent * PerPx;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"HPBAR"));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top,
		m_tInfo.FCX - fValue, 15,
		hMemDC, 0, 0,
		200, 15, RGB(98, 124, 76));
}

void COMonster_Practice::Release()
{
}

void COMonster_Practice::Move_Left()
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

void COMonster_Practice::Move_Right()
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

void COMonster_Practice::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		switch (m_Character_CurStance)
		{
		case Char_StanceID::WALK_L:
			m_pFrameKey = L"Monster_Ground_Walk_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			break;

		case Char_StanceID::WALK_R:
			m_pFrameKey = L"Monster_Ground_Walk_R";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			break;

		case Char_StanceID::ATTACK_L:
			m_pFrameKey = L"Monster_Ground_Attack_L";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 50;
			break;

		case Char_StanceID::ATTACK_R:
			m_pFrameKey = L"Monster_Ground_Attack_R";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 50;
			break;
		}
		m_Character_PreStance = m_Character_CurStance;
	}
}
