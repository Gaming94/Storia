#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"

#include "ORocoTown.h"


CORocoTown::CORocoTown()
	:StageClear(0)
{
	MonsterCnt = 0;

	Jump_State = false;
	JumpStartPosition = 0;
	JumpPower = 25;
	JumpDistance = 1;
}


CORocoTown::~CORocoTown()
{
	Release();
}

void CORocoTown::Init()
{
	switch (SelectCharacterNumber)
	{
		case eChar_Num::ALPONSO:
		{
			pSellect_Player = AbstractFactory<COAlponso>::CreateObj(300, 700, true);
		}
		break;

		case eChar_Num::LEO:
		{
			pSellect_Player = AbstractFactory<COLeo>::CreateObj(300, 700, true);
		}
		break;
	}

	CObjMgr::GetInstance()->AddObject(pSellect_Player, ObjID::OBJ_CHARACTER);
	pSellect_Player->SetIsBattle(true);
}

void CORocoTown::LateInit()
{
}

int CORocoTown::Update()
{
	pSellect_Player->MoveTutorial(4);

	if (StageClear == true)
	{
		if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
		{
			if (pSellect_Player->GetInfo().FX >= 845)
			{
				if (Scroll <= 520)
				{
					Scrolling = true;
					Scroll += 5;
				}
				else
				{
					Scrolling = false;
				}
			}
		}

		if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
		{
			if (pSellect_Player->GetInfo().FX <= 845)
			{
				if (Scroll >= 1)
				{
					Scrolling = true;
					Scroll -= 5;
				}
				else
				{
					Scrolling = false;
				}
			}
		}
	}

	if (Scrolling == true)
	{
		pSellect_Player->SetPlayerSpeed(0);
	}
	else
	{
		pSellect_Player->SetPlayerSpeed(5);
	}


	if (CKeyMgr::GetInstance()->KeyDown('X'))
	{
		if (m_MonsterMap.empty() == false)
		{
			Iter = m_MonsterMap.begin();

			if (abs(pSellect_Player->GetInfo().FX - Iter->second->GetInfo().FX) >= 200)
			{
				LeoSkillONOFF = true;
			}
		}
	}

	if (CKeyMgr::GetInstance()->KeyUp(VK_RIGHT) || CKeyMgr::GetInstance()->KeyUp(VK_LEFT))
	{
		Scrolling = false;
		pSellect_Player->SetPlayerSpeed(5);
	}
	
	return 0;
}

void CORocoTown::LateUpdate()
{
	if (MonsterCnt >= 0)
	{
		//bool Rand = rand() % 2;
		bool Rand = 1;
		if (Rand == 0)
		{
			CObj* pSellect_Monster = AbstractFactory<COAlponso>::CreateObj(WINCX, 600, false);
			CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);
			m_MonsterMap.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
			pSellect_Monster->SetIsBattle(true);
			pSellect_Monster->BeNpc_Walking();
		}
		else
		{
			CObj* pSellect_Monster = AbstractFactory<COLeo>::CreateObj(WINCX, 600, false);
			CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);
			m_MonsterMap.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
			pSellect_Monster->SetIsBattle(true);
			pSellect_Monster->BeNpc_Walking();
		}

		MonsterCnt--;
	}

	if (!m_MonsterMap.empty())
	{
		Iter = m_MonsterMap.begin();
		for (Iter; Iter != m_MonsterMap.end(); Iter++)
		{
			Iter->second->SetTarget(pSellect_Player);
			
			if (Jump_State == false)
			{
				Iter->second->MoveToTarget();
			}
		}

		Iter = m_MonsterMap.begin();
		for (Iter; Iter != m_MonsterMap.end(); Iter++)
		{
			if (Iter->second->GetInfo().FX >= pSellect_Player->GetInfo().FX)
			{
				Iter->second->SetLR(false);
			}
			else
			{
				Iter->second->SetLR(true);
			}
		}

		Iter = m_MonsterMap.begin();
		for (Iter; Iter != m_MonsterMap.end(); Iter++)
		{
			if (abs(Iter->second->GetInfo().FX - pSellect_Player->GetInfo().FX) <= pSellect_Player->GetInfo().FCX *0.5)
			{
				Iter->second->SetPlayerSpeed(0);
				Iter->second->BeNpc_Attacking();
			}
			else
			{
				if (abs(Iter->second->GetInfo().FX - pSellect_Player->GetInfo().FX) >= 400)
				{
					Iter->second->SetPlayerSpeed(5);
				}

				else if (abs(Iter->second->GetInfo().FX - pSellect_Player->GetInfo().FX) >= 150)
				{
					Iter->second->SetPlayerSpeed(4);
				}

				Iter->second->BeNpc_Walking();
			}
		}


		if (LeoSkillONOFF == true)
		{
			Iter = m_MonsterMap.begin();

			bool _LR;

			if (pSellect_Player->GetInfo().FX <= Iter->second->GetInfo().FX)
				_LR = true;
			else
				_LR = false;

			pSellect_Player->SetLR(_LR);
			pSellect_Player->Skeill_X(Iter->second->GetInfo().FX, _LR);
		}

		if (LeoSkillONOFF == true)
		{
			if (abs(pSellect_Player->GetInfo().FX - Iter->second->GetInfo().FX) <= pSellect_Player->GetInfo().FCX)
			{
				ScreenShake = true;
				LeoSkillONOFF = false;
				pSellect_Player->BeNpc_Standing();

				Iter->second->SetDamage(pSellect_Player->GetStatus().Atk);

				Jump_State = true;
				JumpTime = 0;

				if (pSellect_Player->GetLR() == true)
				{
					//Iter->second->SetPos(Iter->second->GetInfo().FX + 100, Iter->second->GetInfo().FY);
					//Iter->second->SetPos(Iter->second->GetInfo().FX, Iter->second->GetInfo().FY - 100);

					JumpStartPosition = Iter->second->GetInfo().FY - 25;
				}
				else
				{
					//Iter->second->SetPos(Iter->second->GetInfo().FX - 100, Iter->second->GetInfo().FY);
					//Iter->second->SetPos(Iter->second->GetInfo().FX, Iter->second->GetInfo().FY);

					JumpStartPosition = Iter->second->GetInfo().FY - 25;
				}
			}
		}

		if (Jump_height < 0.0f)
		{
			Jump_State = false;
			Jump_height = 0;
			JumpTime = 0;

			Iter = m_MonsterMap.begin();
		}

		if (Jump_State == true)
		{
			Iter = m_MonsterMap.begin();
			Iter->second->BENPC_HIT();

			Jump_height = (-JumpTime * JumpTime) + (JumpPower * JumpTime);
			pup = JumpStartPosition - Jump_height;
			Iter->second->SetPos(Iter->second->GetInfo().FX, pup);
			JumpTime += JumpDistance;
		}

		if (ScreenShake == true)
		{
			m_SwiftX = rand() % 7;
			m_SwiftY = rand() % 7;
			ShakeCnt++;
		}

		if (ScreenShake == true)
		{
			if (ShakeCnt >= 10)
			{
				ScreenShake = false;
				m_SwiftX = 0;
				m_SwiftY = 0;
				ShakeCnt = 0;
			}
		}


		Iter = m_MonsterMap.begin();
		for (Iter; Iter != m_MonsterMap.end(); Iter++)
		{
			if (Iter->second->GetStatus().Cur_HP <= 0)
			{
				m_MonsterMap.erase(Iter);

				if (m_MonsterMap.empty() == true)
				{
					StageClear = true;
					break;
				}
				else
				{
					Iter = m_MonsterMap.begin();
				}
			}
		}
	}

	if (StageClear == true)
	{
		if (pSellect_Player->GetInfo().FX >= WINCX)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
		}
	}

}

void CORocoTown::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"RocoTown"));
	BitBlt(hdc, 0 + m_SwiftX, 0 + m_SwiftY, WINCX, WINCY, hMemDC, 0 + Scroll, 0, SRCCOPY);

	//GdiTransparentBlt(hdc, 0, 0, 1892, 849,	hMemDC, 0, 0, 1892, 849, RGB(255, 255, 255));
}

void CORocoTown::Release()
{
}
