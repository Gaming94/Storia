#include "stdafx.h"

#include "OMiniGame.h"
#include "OHorseRace.h"

#include "SMiniGame.h"


CSMiniGame::CSMiniGame()
{
}


CSMiniGame::~CSMiniGame()
{
	Release();
}

void CSMiniGame::Init()
{
	CSoundMgr::GetInstance()->PlaySoundW(L"Theme_of_Lysander.mp3", CSoundMgr::CHANNEL_ID::BGM);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.2);

	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Beroia/Beroia.bmp", L"Beroia");

	CObj* pSellect_MiniGame = AbstractFactory<COHorseRace>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_MiniGame, ObjID::OBJ_MINIGAME);
}

void CSMiniGame::Update()
{
}

void CSMiniGame::LateUpdate()
{
}

void CSMiniGame::Render(HDC hdc)
{
}

void CSMiniGame::Release()
{
	CObjMgr::GetInstance()->Release();
}