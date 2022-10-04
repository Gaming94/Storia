#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"

#include "OMonster_Practice.h"
#include "OMonster_Beach.h"

#include "OAlphaEffect.h"

#include "OBeroia.h"


COBeroia::COBeroia()
	:MaxMonsterCnt(5), MonsterCnt(0)
{
	ScrollMax = 530;
}


COBeroia::~COBeroia()
{
	Release();
}

void COBeroia::Init()
{
	switch (SelectCharacterNumber)
	{
		case eChar_Num::ALPONSO:
		{
			pSellect_Player = AbstractFactory<COAlponso>::CreateObj(-100, 700, true);
		}
		break;

		case eChar_Num::LEO:
		{
			pSellect_Player = AbstractFactory<COLeo>::CreateObj(-100, 700, true);
		}
		break;
	}

	CObjMgr::GetInstance()->AddObject(pSellect_Player, ObjID::OBJ_CHARACTER);
	pSellect_Player->SetIsBattle(true);
	
}

void COBeroia::LateInit()
{
}

int COBeroia::Update()
{
	if (IsStageStart == false)
	{
		//스테이지 시작전 맵 한번 보여주기
		if (isGoto == false)
		{
			if (Scroll <= ScrollMax)
			{
				Scroll += 5;
			}

			if (Scroll >= ScrollMax)
				isGoto = true;
		}
		else
		{
			if (Scroll >= 1)
			{
				Scroll -= 5;
			}

			if (Scroll <= 1)
			{
				IsStageStart = true;
			}
		}

	}

	if (IsStageStart == true)
	{
		pSellect_Player->MoveTutorial(5);
	}

	//스테이지를 클리어했을때 맵 스크롤링가능
	if (StageClear == true)
	{
		ScrollingFnc();
	}
	
	return 0;
}

void COBeroia::LateUpdate()
{
	//임시 몬스터 체크
	//맵 스크롤링이 끝나면 몬스터 한마리가 나온다
	if (IsStageStart == true && MonsterCnt == 0)
	{
		for (int i = 0; i <= 1; i++)
		{
			CObj* pSellect_Monster = new COMonster_Practice;
			MonsterCnt++;

			int SpawnX = rand() % 700 + pSellect_Player->GetInfo().FX;
			int SpawnY = rand() % 20;

			pSellect_Monster = AbstractFactory<COMonster_Beach>::CreateObj(1000 + SpawnX, pSellect_Player->GetInfo().FY + 100 + SpawnY);

			CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);
			Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
		}
	}

	if (Monster_Map.empty() == true && MonsterCnt >= 1)
	{
		// 스테이지당 설정된 최대 몬스터의 개채수만큼 소환
		for (MonsterCnt; MonsterCnt <= MaxMonsterCnt; MonsterCnt++)
		{
			CObj* pSellect_Monster = new COMonster_Practice;

			// 몬스터의 종류 랜덤으로 설정
			int RandMob = rand() % 2;

			// 몬스터의 스폰 XY좌표 설정
			int SpawnX = rand() % 700 + pSellect_Player->GetInfo().FX;
			int SpawnY = rand() % 20;

			if (RandMob == 0)
			{
				pSellect_Monster = AbstractFactory<COMonster_Practice>::CreateObj(SpawnX, pSellect_Player->GetInfo().FY + SpawnY);
				CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);

				Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
			}
			else if (RandMob == 1)
			{
				pSellect_Monster = AbstractFactory<COMonster_Beach>::CreateObj(SpawnX, pSellect_Player->GetInfo().FY + SpawnY);
				CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);

				Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
			}
		}
	}

	if (pSellect_Player->GetStatus().Cur_HP <= 0 && deadswitch == false)
	{
		CEffectMgr::GetInstance()->SetPosition(pSellect_Player->GetRect().left, pSellect_Player->GetRect().top, pSellect_Player->GetRect().right, pSellect_Player->GetRect().bottom);
		CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH);

		pSellect_Player->SetDead();
		deadswitch = true;
	}


	if (Monster_Map.empty() == false)
	{
		Monster_Iter = Monster_Map.begin();
		for (Monster_Iter; Monster_Iter != Monster_Map.end(); Monster_Iter++)
		{
			if (Monster_Iter->second->GetStatus().Cur_HP <= 0)
			{
				CEffectMgr::GetInstance()->SetPosition(Monster_Iter->second->GetRect().left, Monster_Iter->second->GetRect().top, Monster_Iter->second->GetRect().right, Monster_Iter->second->GetRect().bottom);
				CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH);

				Monster_Iter->second->SetDead();
				Monster_Map.erase(Monster_Iter);

				break;
			}
		}

		Monster_Iter = Monster_Map.begin();
		for (Monster_Iter; Monster_Iter != Monster_Map.end(); Monster_Iter++)
		{
			//몬스터의 반경 내에 플레이어가 존재하면 타겟 지정
			if (abs(Monster_Iter->second->GetInfo().FX - pSellect_Player->GetInfo().FX) <= 500)
			{
				if (pSellect_Player->GetStatus().Cur_HP > 0)
				{
					Monster_Iter->second->SetTarget(pSellect_Player);
				}
			}
		}
	}

	//캐릭터 사망시
	if (CKeyMgr::GetInstance()->KeyDown(VK_BACK))
	{
		Alphaswitch = true;

		pSellect_AlphaEffect = AbstractFactory<COAlphaEffect>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_AlphaEffect, ObjID::OBJ_ALPHAEFFECT);
		pSellect_AlphaEffect->SetFadeinout(1);
	}

	if (Alphaswitch == true)
	{
		DummyAlphaOutCnt += 5;
	}


	if (((pSellect_Player->GetChar_CurStance() == Char_StanceID::ATTACK_R) || (pSellect_Player->GetChar_CurStance() == Char_StanceID::ATTACK_L))
		&& (pSellect_Player->GetChar_CurFrame() == 7 && pSellect_Player->GetChar_CurSceneN() == 0))
	{
		ScreenShake = true;
	}

	//화면 흔들기
	if (ScreenShake == true)
	{
		m_SwiftX = rand() % 20;
		m_SwiftY = rand() % 20;
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

	//맵 클리어
	if (StageClear == true)
	{
		if (pSellect_Player->GetInfo().FX >= WINCX || DummyAlphaOutCnt >= 255)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
		}
	}
}

void COBeroia::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Beroia"));
	BitBlt(hdc, 0 + m_SwiftX, 0 + m_SwiftY, WINCX, WINCY, hMemDC, 0 + Scroll, 0, SRCCOPY);
}

void COBeroia::Release()
{
}

void COBeroia::ScrollingFnc()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		if (pSellect_Player->GetInfo().FX >= 845)
		{
			if (Scroll <= 530)
			{
				Scrolling = true;
				Scroll += 5;
			}
			else
			{
				Scrolling = false;
			}
		}

		if (Scrolling == true)
		{
			Monster_Iter = Monster_Map.begin();
			for (Monster_Iter; Monster_Iter != Monster_Map.end(); Monster_Iter++)
			{
				Monster_Iter->second->SetPos(Monster_Iter->second->GetInfo().FX - 5, Monster_Iter->second->GetInfo().FY);
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

		if (Scrolling == true)
		{
			Monster_Iter = Monster_Map.begin();
			for (Monster_Iter; Monster_Iter != Monster_Map.end(); Monster_Iter++)
			{
				Monster_Iter->second->SetPos(Monster_Iter->second->GetInfo().FX + 5, Monster_Iter->second->GetInfo().FY);
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

	if (CKeyMgr::GetInstance()->KeyUp(VK_RIGHT) || CKeyMgr::GetInstance()->KeyUp(VK_LEFT))
	{
		Scrolling = false;
		pSellect_Player->SetPlayerSpeed(5);
	}
}
