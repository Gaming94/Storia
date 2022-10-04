#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"
#include "OAlphaEffect.h"

#include "OSelectMap.h"


COSelectMap::COSelectMap()
	:m_ChoiceMap(0)
{
}


COSelectMap::~COSelectMap()
{
	Release();
}

void COSelectMap::Init()
{
	m_ChoiceMap = ClearMapPos;

	m_SelectMapArrX[0] = 500; m_SelectMapArrY[0] = 240;
	m_SelectMapArrX[1] = 200; m_SelectMapArrY[1] = 420;
	m_SelectMapArrX[2] = 500; m_SelectMapArrY[2] = 520;
	m_SelectMapArrX[3] = 840; m_SelectMapArrY[3] = 440;
	m_SelectMapArrX[4] = 1150; m_SelectMapArrY[4] = 500;
	m_SelectMapArrX[5] = 1020; m_SelectMapArrY[5] = 210;
	m_SelectMapArrX[6] = 1320; m_SelectMapArrY[6] = 250;
	m_SelectMapArrX[7] = 1470; m_SelectMapArrY[7] = 500;

	switch (SelectCharacterNumber)
	{
		case eChar_Num::ALPONSO:
		{
			pSellect_Char = AbstractFactory<COAlponso>::CreateObj(m_SelectMapArrX[m_ChoiceMap], m_SelectMapArrY[m_ChoiceMap], false);
		}
		break;

		case eChar_Num::LEO:
		{
			pSellect_Char = AbstractFactory<COLeo>::CreateObj(m_SelectMapArrX[m_ChoiceMap], m_SelectMapArrY[m_ChoiceMap], false);
		}
		break;
	}

	CObjMgr::GetInstance()->AddObject(pSellect_Char, ObjID::OBJ_CHARACTER);
	pSellect_Char->SetIsBattle(false);

	SelectStageShadow = true;
}

void COSelectMap::LateInit()
{
}

int COSelectMap::Update()
{
	if (m_ChoiceMap == 0)
	{
		pSellect_Char->SetLR(1);
	}

	if (SW_FadeIn == false && SW_FadeOut == false)
	{
		CSoundMgr::GetInstance()->SoundFadeIn(CSoundMgr::CHANNEL_ID::BGM_SelectMap);
		FadeInCnt += 0.007;
	}

	if (FadeInCnt >= 0.3)
	{
		SW_FadeIn = true;
	}
	
	pSellect_Char->BeNpc_Walking();
	pSellect_Char->SetPos(m_SelectMapArrX[m_ChoiceMap], m_SelectMapArrY[m_ChoiceMap]);

	if (CKeyMgr::GetInstance()->KeyDown(VK_RIGHT))
	{
		pSellect_Char->SetLR(1);
		m_ChoiceMap++;
		if (m_ChoiceMap >= 7)
		{
			m_ChoiceMap = 7;
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_LEFT))
	{
		pSellect_Char->SetLR(0);
		m_ChoiceMap--;
		if (m_ChoiceMap <= 0)
		{
			m_ChoiceMap = 0;
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
	{
		SW_FadeOut = true;
	}


	if (SW_FadeOut == true)
	{
		CSoundMgr::GetInstance()->SoundFadeOut(CSoundMgr::CHANNEL_ID::BGM_SelectMap);
		FadeOutCnt -= 0.007;

		if (SW_Alpha == false)
		{
			SW_Alpha = true;

			pSellect_AlphaEffect = AbstractFactory<COAlphaEffect>::CreateObj();
			CObjMgr::GetInstance()->AddObject(pSellect_AlphaEffect, ObjID::OBJ_ALPHAEFFECT);
			pSellect_AlphaEffect->SetFadeinout(1);
		}
	}

	if (SW_FadeOut == true && FadeOutCnt <= 0)
	{
		SelectStageShadow = false;

		//¾ÀÃ¼ÀÎÁö
		switch (m_ChoiceMap)
		{
		case eSelectMap::MAP_ROCOTOWN:
			ClearMapPos = 0;
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_ROCOTOWN);
			break;

		case eSelectMap::MAP_VOLCANO:
			ClearMapPos = 1;
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_VOLCANO);
			break;

		case eSelectMap::MAP_BEROIYA:
			ClearMapPos = 2;
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_BEROIA);
			//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MINIGAME);
			break;

		case eSelectMap::MAP_SANCTUARY:
			ClearMapPos = 3;
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_SANCTUARY);
			break;

		case eSelectMap::MAP_OLDTREE:
			break;
		case eSelectMap::MAP_VALONBREY:
			break;

		case eSelectMap::MAP_RAVEN:
			ClearMapPos = 7;
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_RAVEN);
			break;
		}
	}


	if (Effect > 0)
		Effect -= 40;

	if (Effect <= 0)
		Effect = 0;


	return 0;
}

void COSelectMap::LateUpdate()
{
}

void COSelectMap::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Select_Map"));
	GdiTransparentBlt(hdc, 0, 0, WINCX + Effect, WINCY + Effect, hMemDC, 0, 0, WINCX, WINCY, NULL);
}

void COSelectMap::Release()
{
}
