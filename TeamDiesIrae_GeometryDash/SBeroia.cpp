#include "stdafx.h"

#include "OBeroia.h"

#include "SBeroia.h"


CSBeroia::CSBeroia()
{
}


CSBeroia::~CSBeroia()
{
	Release();
}

void CSBeroia::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Beroia/Beroia.bmp", L"Beroia");

	pSellect_Beroia = AbstractFactory<COBeroia>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Beroia, ObjID::OBJ_BEROIA);

	CSoundMgr::GetInstance()->PlaySoundW(L"Monster.mp3", CSoundMgr::CHANNEL_ID::BGM);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.5);
}

void CSBeroia::Update()
{
}

void CSBeroia::LateUpdate()
{
}

void CSBeroia::Render(HDC hdc)
{
}

void CSBeroia::Release()
{
	CEffectMgr::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::BGM);
}
