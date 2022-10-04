#include "stdafx.h"

#include "OAlponso.h"
#include "OShadow.h"

#include "Attack_Effect.h"


COAlponso::COAlponso()
	:m_Character_IDLE(false)
{
	m_dwPreTick = GetTickCount64();
	m_dwCurTick = GetTickCount64();
}


COAlponso::~COAlponso()
{
	Release();
}

void COAlponso::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Alponso_Standing_L.bmp", L"Alponso_Standing_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Alponso_Standing_R.bmp", L"Alponso_Standing_R");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Alponso_Walk_L.bmp", L"Alponso_Walk_L");
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Alponso_Walk_R.bmp", L"Alponso_Walk_R");

	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/Alponso/Alponso_Attack.bmp", L"Alponso_Attack");

	//실질적 위치
	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	//캐릭터 이동 속도
	m_pSpeed = 5;
	m_pSpeedY = 3;
	m_pShSpeed = 3;

	//프레임단위
	m_pFrameKey = L"Alponso_Standing_L";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.iFrameSceneEnd = 2;
	m_tFrame.dwFrameTime = GetTickCount64();
	m_tFrame.dwFrameSpd = 70;

	m_Character_CurStance = Char_StanceID::IDLE_R;
	m_Character_PreStance = m_Character_CurStance;

	//캐릭터 크기
	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Alponso_Standing_L", L"../Image/Character/Alponso/Alponso_Standing_L.bmp") / (m_tFrame.iFrameEnd + 1);
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Alponso_Standing_L", L"../Image/Character/Alponso/Alponso_Standing_L.bmp") / (m_tFrame.iFrameSceneEnd + 1);

	//점프관련 
	Jump_State = false;
	JumpStartPosition = 0;
	JumpPower = 25;
	JumpDistance = 1;

	pSellect_Shadow = AbstractFactory<COShadow>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Shadow, ObjID::OBJ_SHADOW);
}


void COAlponso::LateInit()
{
}

int COAlponso::Update()
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

		if (m_Start == false)
		{
			//MoveTutorial(m_pSpeed);
		}
		else
		{
			if (m_tInfo.FX >= WINCX)
			{
				m_tInfo.FX = -50;
			}

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_Character_IDLE == false;
			}


			//캐릭터 움직임 //마우스 컨트롤
			if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
			{
				GetCursorPos(&m_ChMove);
				ScreenToClient(g_hWnd, &m_ChMove);

				m_IsMoving = true;

				m_ToDestX = fabs(m_ChMove.x - m_tInfo.FX);

				if (m_ChMove.x >= m_tInfo.FX)
				{
					//오른쪽
					m_IsLR = true;
				}
				else
				{
					//왼쪽
					m_IsLR = false;
				}
			}

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
				m_IsIdle = false;
				m_Character_CurStance = Char_StanceID::ATTACK_R;

				if (m_tFrame.iFrameStart == 0 && m_tFrame.iFrameScene == 1)
				{
					CEffectMgr::GetInstance()->SetPosition(m_tRect.left - 50, m_tRect.top - 135, m_tRect.right - 50, m_tRect.bottom - 135);
					CEffectMgr::GetInstance()->SetWhatChar(2);
					CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERATTACK);
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

	return 0;
}

void COAlponso::LateUpdate()
{
	CKeyMgr::GetInstance()->UpdateKey();
	CObj::MoveFrame();
	CObj::UpdateRect();
	SceneChange();

	if (LodingShadow == true)
	{
		if (m_IsLR == true)
		{
			pSellect_Shadow->SetPos(m_tRect.right - 99, m_tRect.bottom - 13);
		}
		else
		{
			pSellect_Shadow->SetPos(m_tRect.left + 99, m_tRect.bottom - 13);
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

	//if (m_ObjectMove == true)
	//{
	//	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE) && !Jump_State)
	//	{
	//		Jump_State = true;
	//		JumpTime = 0;
	//		JumpStartPosition = m_tInfo.FY;
	//	}
	//
	//	if (Jump_State == true)
	//	{
	//		Jump();
	//	}
	//
	//	if (Jump_height < 0.0f)
	//	{
	//		Jump_State = false;
	//		Jump_height = 0;
	//		JumpTime = 0;
	//	}
	//}
}

void COAlponso::Render(HDC hdc)
{
	CObj::UpdateRect();
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(m_pFrameKey));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tInfo.FCX, m_tInfo.FCY,	
		hMemDC, m_tInfo.FCX * m_tFrame.iFrameStart, m_tInfo.FCY * m_tFrame.iFrameScene, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));


	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void COAlponso::Release()
{
}

void COAlponso::SceneChange()
{
	if (m_Character_PreStance != m_Character_CurStance)
	{
		switch (m_Character_CurStance)
		{
		case Char_StanceID::IDLE_L:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Alponso_Standing_L";
			break;

		case Char_StanceID::IDLE_R:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Alponso_Standing_R";
			break;

		case Char_StanceID::WALK_L:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Alponso_Walk_L";
			break;

		case Char_StanceID::WALK_R:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 70;
			m_pFrameKey = L"Alponso_Walk_R";
			break;

		case Char_StanceID::ATTACK_R:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.iFrameSceneEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount64();
			m_tFrame.dwFrameSpd = 60;
			m_pFrameKey = L"Alponso_Attack";
			break;
		}
		m_Character_PreStance = m_Character_CurStance;
	}
}

void COAlponso::Jump()
{
	Jump_height = -JumpTime * JumpTime + JumpPower * JumpTime;
	m_tInfo.FY = JumpStartPosition - Jump_height;
	JumpTime += JumpDistance;
}

void COAlponso::Walk()
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
