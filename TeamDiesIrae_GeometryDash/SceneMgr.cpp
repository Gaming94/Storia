#include "stdafx.h"
#include "Scene.h"

//
#include "SLoading.h"
#include "SSelectCharacter.h"
#include "SSelectMode.h"
#include "STutorial.h"
#include "SSelectStage.h"
#include "SRocoTown.h"
#include "SVolcano.h"
#include "SBeroia.h"
#include "SSanctuary.h"
#include "SRaven.h"

#include "SMiniGame.h"
//

#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstacne = nullptr;

CSceneMgr::CSceneMgr()
	:m_eCurScene(SCENE_END), m_ePreScene(SCENE_END)
{
	dwBackScroll = GetTickCount64();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Init()
{
}

int CSceneMgr::Update()
{
	m_pScene->Update();
	return 0;
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hdc)
{
	m_pScene->Render(hdc);
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
	CObjMgr::GetInstance()->Release();
}

void CSceneMgr::SceneChange(SCENEID eID)
{
	m_eCurScene = eID;

	// 씬이 전환되었을때
	if (m_ePreScene != m_eCurScene)
	{
		// 이전 씬 할당 해제합니다
		Release();

		switch (m_eCurScene)
		{
			// 로딩 씬
			case CSceneMgr::SCENE_LOADING:
			{
				m_pScene = new CSLoading;
			}
			break;

			// 캐릭터 선택 씬
			case CSceneMgr::SCENE_SELECTCHARACTER:
			{
				m_pScene = new CSSelectCharacter;
			}
			break;

			// 튜토리얼 씬
			case CSceneMgr::SCENE_TUTORIAL:
			{
				m_pScene = new CSTutorial;
			}
			break;

			case CSceneMgr::SCENE_SELECTSTAGE:
			{
				m_pScene = new CSSelectStage;
			}
			break;

			case CSceneMgr::SCENE_MAP_ROCOTOWN:
			{
				m_pScene = new CSRocoTown;
			}
			break;

			case CSceneMgr::SCENE_MAP_VOLCANO:
			{
				m_pScene = new CSVolcano;
			}
			break;

			case CSceneMgr::SCENE_MAP_BEROIA:
			{
				m_pScene = new CSBeroia;
			}
			break;

			case CSceneMgr::SCENE_MAP_SANCTUARY:
			{
				m_pScene = new CSSanctuary;
			}
			break;

			case CSceneMgr::SCENE_MAP_RAVEN:
			{
				m_pScene = new CSRaven;
			}
			break;

			case CSceneMgr::SCENE_SELECTMODE:
			{
				m_pScene = new CSSelectMode;
			}
			break;

			//수업내용 //임시보류
			case CSceneMgr::SCENE_MINIGAME:
			{
				m_pScene = new CSMiniGame;
			}
			break;
		}
		
		// 다음 씬으로 선택된 씬객체의 Init 함수를 실행한다
		m_pScene->Init();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::GameStart(HDC hdc)
{
}
