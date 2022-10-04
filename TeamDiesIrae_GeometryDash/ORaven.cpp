#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"
#include "OBoss.h"

#include "OMonster_Practice.h"
#include "OMonster_Beach.h"

//배경 이펙트
#include "OBckGroundEffect.h"

#include "OAlphaEffect.h"

#include "ORaven.h"

CORaven::CORaven()
	:deadswitch(false), DummyAlphaInCnt(0), DummyAlphaOutCnt(0)
{
}

CORaven::~CORaven()
{
	Release();
}

void CORaven::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Raven/Raven_Field2.bmp", L"Raven_Field");

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


	pSellect_BackGroundEffect1 = AbstractFactory<COBckGroundEffect>::CreateObj(1000, 200);
	CObjMgr::GetInstance()->AddObject(pSellect_BackGroundEffect1, ObjID::OBJ_BG_EFFECT);
	
	pSellect_BackGroundEffect2 = AbstractFactory<COBckGroundEffect>::CreateObj(-500, 200);
	CObjMgr::GetInstance()->AddObject(pSellect_BackGroundEffect2, ObjID::OBJ_BG_EFFECT);

	pSellect_Boss = AbstractFactory<COBoss>::CreateObj(WINCX, 500);
	CObjMgr::GetInstance()->AddObject(pSellect_Boss, ObjID::OBJ_MONSTER);

	pSellect_Boss->SetTarget(pSellect_Player);
}

void CORaven::LateInit()
{
}

int CORaven::Update()
{
	if (CKeyMgr::GetInstance()->KeyDown('Q'))
	{
		pSellect_Player->SetPlayerRevive();
	}


    return 0;
}

void CORaven::LateUpdate()
{
	if (SW_AlphaIn == false && Alphaswitch == false)
	{
		SW_AlphaIn = true;

		pSellect_AlphaInEffect = AbstractFactory<COAlphaEffect>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_AlphaInEffect, ObjID::OBJ_ALPHAEFFECT);
		pSellect_AlphaInEffect->SetFadeinout(0);
	}

	//if (pSellect_Boss->GetStatus().Cur_HP >= 0)
	//{
	//	//몬스터 스폰
	//	if (MonsterCnt == 0 && SpawnSwitch == true)
	//	{
	//		for (int i = 0; i <= 1; i++)
	//		{
	//			MonsterCnt++;
	//
	//			CObj* pSellect_Monster = new COMonster_Beach;
	//
	//			pSellect_Monster = AbstractFactory<COMonster_Beach>::CreateObj(WINCX + 700, pSellect_Player->GetInfo().FY + 30);
	//			CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);
	//			Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
	//
	//			pSellect_Monster->SetTarget(pSellect_Player);
	//			pSellect_Monster->SetMonsterSpeed(3);
	//		}
	//	}
	//
	//	Monster_Iter = Monster_Map.begin();
	//	for (Monster_Iter; Monster_Iter != Monster_Map.end(); Monster_Iter++)
	//	{
	//		if (Monster_Iter->second->GetStatus().Cur_HP <= 0)
	//		{
	//			CEffectMgr::GetInstance()->SetPosition(Monster_Iter->second->GetRect().left, Monster_Iter->second->GetRect().top, Monster_Iter->second->GetRect().right, Monster_Iter->second->GetRect().bottom);
	//			CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH);
	//
	//			Monster_Iter->second->SetDead();
	//			Monster_Map.erase(Monster_Iter);
	//
	//			MonsterCnt--;
	//
	//			break;
	//		}
	//	}
	//}


	//보스관련
	if (pSellect_Boss != NULL)
	{
		//화면진동
		if (((pSellect_Boss->GetChar_CurStance() == Char_StanceID::ATTACK_L))
			&& (pSellect_Boss->GetChar_CurFrame() == 4 && pSellect_Boss->GetChar_CurSceneN() == 1))
		{
			ScreenShake = true;
		}

		//보스 사망시
		if (pSellect_Boss->GetStatus().Cur_HP <= 0)
		{
			CEffectMgr::GetInstance()->SetPosition(pSellect_Boss->GetRect().left, pSellect_Boss->GetRect().top, pSellect_Boss->GetRect().right, pSellect_Boss->GetRect().bottom);
			CEffectMgr::GetInstance()->SetObjectType(1);//보스
			CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH);

			pSellect_Boss = NULL;
		}
	}

	//캐릭터 사망시
	if (pSellect_Player->GetStatus().Cur_HP <= 0 && deadswitch == false)
	{
		CEffectMgr::GetInstance()->SetPosition(pSellect_Player->GetRect().left, pSellect_Player->GetRect().top, pSellect_Player->GetRect().right, pSellect_Player->GetRect().bottom);
		CEffectMgr::GetInstance()->SetObjectType(0);//보스
		CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_PLAYERDEATH);

		pSellect_Player->SetDead();
		deadswitch = true;
	}

	//화면 흔들기
	if (ScreenShake == true)
	{
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

	if (deadswitch == true && Alphaswitch == false)
	{
		Alphaswitch = true;

		pSellect_AlphaEffect = AbstractFactory<COAlphaEffect>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_AlphaEffect, ObjID::OBJ_ALPHAEFFECT);
		pSellect_AlphaEffect->SetFadeinout(1);
	}

	if (DummyAlphaOutCnt <= 255 && Alphaswitch == true)
	{
		DummyAlphaOutCnt += 5;
		CSoundMgr::GetInstance()->SoundFadeOut(CSoundMgr::CHANNEL_ID::BGM);
	}

	if (DummyAlphaInCnt <=255 && SW_AlphaIn == true)
	{
		DummyAlphaInCnt += 5;
	}

	if (DummyAlphaInCnt >= 250)
	{
		pSellect_Player->MoveTutorial(5);
		pSellect_AlphaInEffect->SetDead();

		SpawnSwitch = true;
	}

	if (DummyAlphaOutCnt >= 250)
	{
		pSellect_AlphaEffect->SetDead();
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
	}
}

void CORaven::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Raven_Field"));
	GdiTransparentBlt(hdc, 0, 0 + m_SwiftY, WINCX, WINCY,
		hMemDC, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
	
	//BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CORaven::Release()
{
}
