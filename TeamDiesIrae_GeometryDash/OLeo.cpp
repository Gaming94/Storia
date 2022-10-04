#include "stdafx.h"

#include "COAttackRect.h"
#include "OShadow.h"

#include "OLeo.h"


COLeo::COLeo()
	:m_Character_IDLE(0), m_IsMoving(0), m_ToDestX(0)
{
}


COLeo::~COLeo()
{
	Release();
}

void COLeo::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Standing_L.bmp", L"Leo_Standing_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Standing_R.bmp", L"Leo_Standing_R");
	
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Walk_L.bmp", L"Leo_Walk_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Walk_R.bmp", L"Leo_Walk_R");
	
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Attack_L.bmp", L"Leo_Attack_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Attack_R.bmp", L"Leo_Attack_R");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_X_L2.bmp", L"Leo_X_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_X_R2.bmp", L"Leo_X_R");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Attacked_L.bmp", L"Leo_Attacked_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Attacked_R.bmp", L"Leo_Attacked_R");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Hit_L.bmp", L"Leo_Hit_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Leo/Leo_Hit_R.bmp", L"Leo_Hit_R");

	//실질적 위치
	//m_tInfo.FX = -100;
	//m_tInfo.FY = -100;

	//캐릭터 이동 속도
	m_pSpeed = 5;
	m_pSpeedY = 3;
	m_pShSpeed = 3;

	//프레임단위
	m_pFrameKey = L"Leo_Standing_R";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	m_Character_CurStance = Char_StanceID::IDLE_R;
	m_Character_PreStance = m_Character_CurStance;

	//캐릭터 크기
	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Leo_Standing_R", L"../Image/Character/Leo/Leo_Standing_R.bmp") / (m_tFrame.iFrameEnd + 1);
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Leo_Standing_R", L"../Image/Character/Leo/Leo_Standing_R.bmp") / (m_tFrame.iFrameSceneEnd + 1);


	//점프관련 
	Jump_State = false;
	JumpStartPosition = 0;
	JumpPower = 25;
	JumpDistance = 1;

	m_ChMove = {};

	m_tStatus.Atk = 10;
	m_tStatus.Def = 5;
	m_tStatus.MAX_HP = 351;
	m_tStatus.Cur_HP = m_tStatus.MAX_HP;
	m_tStatus.Potion = 0;
	m_tStatus.Money = 859;
	m_tStatus.Weapon = 0;

	pSellect_AttackRect = AbstractFactory<COAttackRect>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_AttackRect, ObjID::OBJ_ATTACKRECT);

	pSellect_Shadow = AbstractFactory<COShadow>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Shadow, ObjID::OBJ_SHADOW);
}

void COLeo::LateInit()
{

}

int COLeo::Update()
{
	if (m_IsIdle == true)
	{
		if (m_IsLR == 1)
		{
			m_Character_CurStance = Char_StanceID::IDLE_R;
		}
		else
		{
			m_Character_CurStance = Char_StanceID::IDLE_L;
		}
	}


	if (m_ObjectMove == true)
	{
		if (m_IsLR == true)
		{
			pSellect_AttackRect->SetPos(m_tInfo.FX + 50, m_tInfo.FY + 10);
		}
		else
		{
			pSellect_AttackRect->SetPos(m_tInfo.FX - 50, m_tInfo.FY + 10);
		}

		if (m_Start == false)
		{
			//MoveTutorial(m_pSpeed);
		}
		else
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_Character_IDLE == false;
			}


			//캐릭터 움직임 //마우스 컨트롤
			//if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
			//{
			//	GetCursorPos(&m_ChMove);
			//	ScreenToClient(g_hWnd, &m_ChMove);
			//
			//	m_IsMoving = true;
			//
			//	m_ToDestX = fabs(m_ChMove.x - m_tInfo.FX);
			//
			//	if (m_ChMove.x >= m_tInfo.FX)
			//	{
			//		//오른쪽
			//		m_IsLR = true;
			//	}
			//	else
			//	{
			//		//왼쪽
			//		m_IsLR = false;
			//	}
			//}

			if (m_IsMoving == true)
			{
				Walk();
				m_IsIdle = false;
			}

			if (m_ToDestX <= 0 && m_ToDestY <= 0)
			{
				m_IsMoving = false;
				m_IsIdle = true;
			}

			//캐릭터 움직임 //키보드 컨트롤
			if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
			{
				m_IsMoving = true;
				m_IsIdle = false;
				
				if (m_IsLR == true)
				{
					m_Character_CurStance = Char_StanceID::WALK_R;
				}
				else
				{
					m_Character_CurStance = Char_StanceID::WALK_L;
				}

				if (m_tInfo.FY >= 600)
				{
					m_tInfo.FY -= m_pSpeedY;
				}
			}
			
			if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
			{
				m_IsMoving = true;
				m_IsIdle = false;
				
				if (m_IsLR == true)
				{
					m_Character_CurStance = Char_StanceID::WALK_R;
				}
				else
				{
					m_Character_CurStance = Char_StanceID::WALK_L;
				}

				if (m_tRect.bottom <= WINCY)
				{
					m_tInfo.FY += m_pSpeedY;
				}
			}
			
			if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
			{
				m_IsMoving = true;
				m_IsIdle = false;
				m_Character_CurStance = Char_StanceID::WALK_R;

				if (CKeyMgr::GetInstance()->KeyPressing(VK_SHIFT))
				{
					m_tInfo.FX += m_pShSpeed;
				}
				m_tInfo.FX += m_pSpeed;
				m_IsLR = true;
			}
			
			if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
			{
				m_IsMoving = true;
				m_IsIdle = false;
				m_Character_CurStance = Char_StanceID::WALK_L;

				if (CKeyMgr::GetInstance()->KeyPressing(VK_SHIFT))
				{
					m_tInfo.FX -= m_pShSpeed;
				}
				m_tInfo.FX -= m_pSpeed;
				m_IsLR = false;
			}

			if (CKeyMgr::GetInstance()->KeyPressing(VK_CONTROL) && m_IsMoving != true)
			{
				m_IsAttacking = true;
				m_IsIdle = false;

				if (m_IsLR == true)
				{
					m_Character_CurStance = Char_StanceID::ATTACK_R;
				}
				else
				{
					m_Character_CurStance = Char_StanceID::ATTACK_L;
				}
			
				bool SoundCheck = false;

				if ((m_tFrame.iFrameStart == 2 && m_tFrame.iFrameScene == 0) && SoundCheck == false)
				{
					SoundCheck = true;
					CSoundMgr::GetInstance()->PlaySoundW(L"Sword2.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
					CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.1);
				}
			}

			//공격했을때를 대비해서 남겨놔
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_Character_IDLE = false;
			}
			//END
		}
	}


	if (CKeyMgr::GetInstance()->KeyDown('O'))
	{
		Jump_State = true;
		JumpTime = 0;
		JumpStartPosition = m_tInfo.FY - 25;

		m_JumpShadowY = pSellect_Shadow->GetInfo().FY;
	}

	if (CKeyMgr::GetInstance()->KeyDown('P'))
	{
		m_tStatus.Cur_HP -= 50;
	}

	if (m_tStatus.Cur_HP <= 0 || m_bIsDead == true)
	{
		pSellect_Shadow->SetDead();
		return DEAD_EVENT;
	}


	if (CKeyMgr::GetInstance()->KeyPressing('C'))
	{
		m_IsIdle = false;
		m_Character_CurStance = Char_StanceID::SKILL_R;

		if (m_tFrame.iFrameStart == 0 && m_tFrame.iFrameScene == 1)
		{
			CEffectMgr::GetInstance()->SetPosition(m_tRect.left + 100, m_tRect.top + 50, m_tRect.right + 100, m_tRect.bottom + 50);
			CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYER_CSKILL);
		}
	}

	return 0;
}

void COLeo::LateUpdate()
{
	CKeyMgr::GetInstance()->UpdateKey();
	CObj::MoveFrame();
	CObj::UpdateRect();
	SceneChange();

	if (SelectStageShadow == false)
	{
		if (m_IsLR == true)
		{
			pSellect_Shadow->SetPos(m_tRect.right - 100, m_tRect.bottom - 10);
		}
		else
		{
			pSellect_Shadow->SetPos(m_tRect.left + 100, m_tRect.bottom - 10);
		}
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameScene++;
		m_tFrame.iFrameStart = 0;
	}

	if (m_tFrame.iFrameScene >= m_tFrame.iFrameSceneEnd)
	{
		m_tFrame.iFrameScene = 0;
	}

	if (m_ObjectMove == true)
	{
		if (Jump_height < 0.0f)
		{
			Jump_State = false;
			Jump_height = 0;
			JumpTime = 0;
		}

		if (Jump_State == true)
		{
			pSellect_Shadow->SetPos(m_tInfo.FX - 50, m_JumpShadowY);
			
			Jump();
		}
	}

	if (CKeyMgr::GetInstance()->KeyPressing('Z') && m_IsMoving != true)
	{
		m_IsIdle = false;
		m_Character_CurStance = Char_StanceID::SKILL_R;

		if (m_tFrame.iFrameStart == 0 && m_tFrame.iFrameScene == 1)
		{
			CEffectMgr::GetInstance()->SetPosition(m_tRect.left + 100, m_tRect.top + 50, m_tRect.right + 100, m_tRect.bottom + 50);
			CEffectMgr::GetInstance()->SetWhatChar(1);
			CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERATTACK);
		}
	}



}

void COLeo::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,
			hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));

	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

	if (m_IsBattle == true)
	{
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
}

void COLeo::Release()
{
}

void COLeo::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		switch (m_Character_CurStance)
		{
		case Char_StanceID::IDLE_R:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Standing_R";
			break;

		case Char_StanceID::IDLE_L:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Standing_L";
			break;

		case Char_StanceID::WALK_R:
			m_tInfo.FCX = 170;
			
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Walk_R";
			break;

		case Char_StanceID::WALK_L:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Walk_L";
			break;

		case Char_StanceID::ATTACK_R:
			m_tInfo.FCX = 198;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 40;
			m_pFrameKey = L"Leo_Attack_R";
			break;

		case Char_StanceID::SKILL_R:
			m_tInfo.FCX = 198;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 40;
			m_pFrameKey = L"Leo_Attack_R";
			break;

		case Char_StanceID::ATTACK_L:
			m_tInfo.FCX = 198;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 40;
			m_pFrameKey = L"Leo_Attack_L";
			break;

		case Char_StanceID::SKILL_X_L:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_X_L";
			break;

		case Char_StanceID::SKILL_X_R:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_X_R";
			break;

		case Char_StanceID::HIT_L:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Hit_L";
			break;

		case Char_StanceID::HIT_R:
			m_tInfo.FCX = 170;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Leo_Hit_R";
			break;
		}
		m_Character_PreStance = m_Character_CurStance;
	}
}



void COLeo::Jump()
{
	Jump_height = (-JumpTime * JumpTime) + (JumpPower * JumpTime);
	m_tInfo.FY = JumpStartPosition - Jump_height;
	JumpTime += JumpDistance;
}

void COLeo::Walk()
{
	if (m_ToDestX >= 0)
	{
		if (m_tInfo.FX <= m_ChMove.x)
		{
			m_tInfo.FX += m_pSpeed;

			m_Character_CurStance = Char_StanceID::WALK_R;
		}

		if (m_tInfo.FX >= m_ChMove.x)
		{
			m_tInfo.FX -= m_pSpeed;

			m_Character_CurStance = Char_StanceID::WALK_L;
		}
		m_ToDestX -= m_pSpeed;
	}
}
