#include "stdafx.h"

#include "OVolcano.h"

#include "SVolcano.h"


CSVolcano::CSVolcano()
{
}


CSVolcano::~CSVolcano()
{
	Release();
}

void CSVolcano::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Volcano/Volcano.bmp", L"Volcano");

	pSellect_Volcano = AbstractFactory<COVolcano>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Volcano, ObjID::OBJ_VOLACONO);

	CSoundMgr::GetInstance()->PlaySoundW(L"Monster.mp3", CSoundMgr::CHANNEL_ID::BGM);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.5);
}

void CSVolcano::Update()
{
}

void CSVolcano::LateUpdate()
{
}

void CSVolcano::Render(HDC hdc)
{
}

void CSVolcano::Release()
{
	CObjMgr::GetInstance()->Release();
	CEffectMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::BGM);
}
