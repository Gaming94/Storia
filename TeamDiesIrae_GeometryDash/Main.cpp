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

	//�� ���
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/BackGround_Stance.bmp", L"BackBuffer");

	//HPBAR
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Character/HPBAR.bmp", L"HPBAR");

	//������
	CSceneMgr::GetInstance()->Init();
		
	//�ε�
	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_LOADING);
	
	//ĳ���ͼ���
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTCHARACTER);
	
	//Ʃ�丮�� //�����⺻
	//SelectCharacterNumber = 1;
	//SelectCharacterNumber = 2;
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_TUTORIAL);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_ROCOTOWN);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_VOLCANO);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_BEROIA);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_SANCTUARY);
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MAP_RAVEN);
	
	//�����ߴ� �ϴ� ����
	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MINIGAME);

	CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_NULL);
}

void CMain::Update()
{
	CSceneMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CEffectMgr::GetInstance()->Update();

	//���� ���� Ÿ�� on off ����ġ
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
