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

	// ���� ��ȯ�Ǿ�����
	if (m_ePreScene != m_eCurScene)
	{
		// ���� �� �Ҵ� �����մϴ�
		Release();

		switch (m_eCurScene)
		{
			// �ε� ��
			case CSceneMgr::SCENE_LOADING:
			{
				m_pScene = new CSLoading;
			}
			break;

			// ĳ���� ���� ��
			case CSceneMgr::SCENE_SELECTCHARACTER:
			{
				m_pScene = new CSSelectCharacter;
			}
			break;

			// Ʃ�丮�� ��
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

			//�������� //�ӽú���
			case CSceneMgr::SCENE_MINIGAME:
			{
				m_pScene = new CSMiniGame;
			}
			break;
		}
		
		// ���� ������ ���õ� ����ü�� Init �Լ��� �����Ѵ�
		m_pScene->Init();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::GameStart(HDC hdc)
{
}
