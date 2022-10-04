#include "stdafx.h"

#include "OSanctuary.h"

#include "SSanctuary.h"

CSSanctuary::CSSanctuary()
{
}

CSSanctuary::~CSSanctuary()
{
	Release();
}

void CSSanctuary::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Sanctuary/Sanctuary.bmp", L"Sanctuary");
	
	pSellect_Sanctuary = AbstractFactory<COSanctuary>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Sanctuary, ObjID::OBJ_SANCTUARY);

	CSoundMgr::GetInstance()->PlaySoundW(L"Epic7_Robby.mp3", CSoundMgr::CHANNEL_ID::BGM);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.3);
}

void CSSanctuary::Update()
{
}

void CSSanctuary::LateUpdate()
{
}

void CSSanctuary::Render(HDC hdc)
{
}

void CSSanctuary::Release()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::BGM);
	CObjMgr::GetInstance()->Release();
}
