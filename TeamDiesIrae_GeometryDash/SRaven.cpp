#include "stdafx.h"

#include "ORaven.h"

#include "SRaven.h"

CSRaven::CSRaven()
{
}

CSRaven::~CSRaven()
{
}

void CSRaven::Init()
{
	// 기초 배경화면
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Raven/Raven_BackGround.bmp", L"Raven_BackGround");

	// 
	CObj* pSellect_RocoTown = AbstractFactory<CORaven>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_RocoTown, ObjID::OBJ_RAVEN);


	CSoundMgr::GetInstance()->PlaySoundW(L"BeTheStar_NightMare.mp3", CSoundMgr::CHANNEL_ID::BGM);
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.2);
}

void CSRaven::Update()
{
}

void CSRaven::LateUpdate()
{
}

void CSRaven::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Raven_BackGround"));
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CSRaven::Release()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::BGM);
	CObjMgr::GetInstance()->Release();
}
