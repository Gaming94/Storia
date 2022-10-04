#include "stdafx.h"
#include "Main.h"


CMain::CMain()
{
}


CMain::~CMain()
{
	Release();
}

void CMain::Init()
{
	CSoundMgr::GetInstance()->Init();
	m_hdc = GetDC(g_hWnd);
	srand((unsigned)time(nullptr));

	//밖 배경
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/BackGround_Stance.bmp", L"BackBuffer");

	//HPBAR
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/HPBAR.bmp", L"HPBAR");

	//씬설정
	CSceneMgr::GetInstance()->Init();
		
	//로딩
	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_LOADING);
	
	//캐릭터설정
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTCHARACTER);
	
	//튜토리얼 //레오기본
	//SelectCharacterNumber = 1;
	//SelectCharacterNumber = 2;
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_TUTORIAL);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_ROCOTOWN);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_VOLCANO);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_BEROIA);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_SANCTUARY);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_RAVEN);
	
	//개발중단 일단 보류
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MINIGAME);

	CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_NULL);
}

void CMain::Update()
{
	CSceneMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CEffectMgr::GetInstance()->Update();

	//몬스터 다중 타격 on off 스위치
	if (CKeyMgr::GetInstance()->KeyDown(VK_TAB))
	{
		if (Overlap_Hit == true)
			Overlap_Hit = false;
		else
			Overlap_Hit = true;
	}
}

void CMain::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
	CEffectMgr::GetInstance()->LateUpdate();
	CKeyMgr::GetInstance()->UpdateKey();
	CSoundMgr::GetInstance()->UpdateSound();
}

void CMain::Render()
{
	HDC hBackBuffer = nullptr;
	HDC hEffectBuffer = nullptr;

	NULL_CHECK(hBackBuffer = CBMPMgr::GetInstance()->FindBackGroundImage(L"BackBuffer"));
	BitBlt(m_hdc, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);

	CSceneMgr::GetInstance()->Render(hBackBuffer);
	CEffectMgr::GetInstance()->Render(hEffectBuffer);
	CObjMgr::GetInstance()->Render(hBackBuffer);
}

void CMain::Release()
{
	ReleaseDC(g_hWnd, m_hdc);

	CSceneMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CEffectMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CBMPMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
}
