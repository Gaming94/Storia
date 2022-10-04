#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:TextOutCnt(0), TextBoxOnOff(0), m_IsLR(1)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tCursorPos, sizeof(POINT));
}


CObj::~CObj()
{
}


void CObj::MoveToTarget()
{
	BeNpc_Walking();
	if (m_tInfo.FX >= pTarget->GetInfo().FX)
	{
		m_tInfo.FX -= m_pSpeed;
	}
	if (m_tInfo.FX <= pTarget->GetInfo().FX)
	{
		m_tInfo.FX += m_pSpeed;
	}

	if (m_tInfo.FY >= pTarget->GetInfo().FY - 100)
	{
		m_tInfo.FY -= m_pSpeedY;
	}

	if (m_tInfo.FY <= pTarget->GetInfo().FY + 50)
	{
		m_tInfo.FY += m_pSpeedY;
	}
}

void CObj::SetPlayerWeapon(int _WeaponNumber)
{
	m_tStatus.Atk = 10;
	m_tStatus.Weapon = _WeaponNumber;

	if (m_tStatus.Weapon == 1)
		m_tStatus.Atk += 10;

	else if(m_tStatus.Weapon == 2)
		m_tStatus.Atk += 15;

	else if (m_tStatus.Weapon == 3)
		m_tStatus.Atk += 20;
}

void CObj::SetPlayerMoney(bool _bs, int _Money)
{
	if (_bs == false)
	{
		m_tStatus.Money -= _Money;
	}
	else
	{
		m_tStatus.Money += _Money;
	}
}

void CObj::Skeill_X(int _Dst, bool _LR)
{

	if (_LR == true)
	{
		m_Character_CurStance = Char_StanceID::SKILL_X_L;

		if (m_tInfo.FX <= _Dst - m_tInfo.FCX)
		{
			m_tInfo.FX += 22;
		}
	}
	else
	{
		m_Character_CurStance = Char_StanceID::SKILL_X_R;

		if (m_tInfo.FX >= _Dst + m_tInfo.FCX)
		{
			m_tInfo.FX -= 22;
		}
	}
}

void CObj::SetPuzzlePos(int x, int y)
{
	m_tPuzzleInfo.FX = x;
	m_tPuzzleInfo.FY = y;
}

void CObj::ChangePuzzle(CObj** _Src, CObj** _Dest)
{
	CObj* Temp = *_Dest;
	*_Dest = *_Src;
	*_Src = Temp;
}

void CObj::LateInit()
{
}

void CObj::CanMoveInit(bool _TF)
{
	m_ObjectMove = _TF;
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.FX - m_tInfo.FCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.FY - m_tInfo.FCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.FX + m_tInfo.FCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.FY + m_tInfo.FCY * 0.5f);
}

void CObj::UpdateInfo()
{
	m_tInfo.FX = LONG((float)(m_tRect.right - m_tRect.left) * 0.5f);
	m_tInfo.FY = LONG((float)(m_tRect.bottom - m_tRect.top) * 0.5f);
}

void CObj::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpd < GetTickCount64())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount64();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;
	}
}

void CObj::MoveSkillFrame()
{
	if (m_tSkillFrame.dwFrameTime + m_tSkillFrame.dwFrameSpd < GetTickCount64())
	{
		m_tSkillFrame.iFrameStart++;
		m_tSkillFrame.dwFrameTime = GetTickCount64();
	}

	if (m_tSkillFrame.iFrameStart > m_tSkillFrame.iFrameEnd)
		m_tSkillFrame.iFrameStart = 0;
}

void CObj::MoveTo(bool _LR)
{
	if (_LR)
	{
		m_Character_CurStance = Char_StanceID::WALK_R;
		m_tInfo.FX += m_pSpeed;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::WALK_L;
		m_tInfo.FX -= m_pSpeed;
	}
}

void CObj::MoveSelectCharacter(int _pSpeed, float _Dest)
{
	if (m_tInfo.FX <= _Dest)
	{
		m_tInfo.FX += _pSpeed;
		m_Character_CurStance = Char_StanceID::WALK_R;
	}

	if (m_tInfo.FX >= _Dest)
	{
		m_Character_CurStance = Char_StanceID::WALK_L;
	}
}

void CObj::MoveTutorial(int _pSpeed)
{
	if (m_Start == false)
	{
		if (m_tInfo.FX <= 300)
		{
			m_tInfo.FX += _pSpeed;
			m_Character_CurStance = Char_StanceID::WALK_R;

			if (m_tInfo.FX >= 300)
			{
				m_Start = true;
			}
		}
	}
}

void CObj::MoveHorseRace(int _Dst)
{
	if (m_tInfo.FX <= _Dst)
	{
		m_tInfo.FX += m_pSpeed;
		m_Character_CurStance = Char_StanceID::WALK_R;

		if (m_tInfo.FX >= _Dst)
		{
			m_Character_CurStance = Char_StanceID::IDLE_R;
		}
	}
}

void CObj::BeNpc_Standing()
{
	if (m_IsLR == true)
	{
		m_Character_CurStance = Char_StanceID::IDLE_R;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::IDLE_L;
	}
}

void CObj::BeNpc_Attacking()
{
	if (m_IsLR == true)
	{
		m_Character_CurStance = Char_StanceID::ATTACK_R;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::ATTACK_L;
	}
}

void CObj::BeNpc_Walking()
{
	if (m_IsLR == true)
	{
		m_Character_CurStance = Char_StanceID::WALK_R;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::WALK_L;
	}
}

void CObj::BENPC_HIT()
{
	if (m_IsLR == true)
	{
		m_Character_CurStance = Char_StanceID::HIT_R;
	}
	else
	{
		m_Character_CurStance = Char_StanceID::HIT_L;
	}
}

void CObj::HitBySkillCOnOff()
{
	SW_HitBySkillC = true;
}
