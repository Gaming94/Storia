#include "stdafx.h"

#include "OSelectMap.h"

#include "SSelectStage.h"


CSSelectStage::CSSelectStage()
{
}


CSSelectStage::~CSSelectStage()
{
	Release();
}

void CSSelectStage::Init()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ID::BGM);

	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/Select_Map/BmpTest.bmp", L"Select_Map");

	pSellect_SelectStage = AbstractFactory<COSelectMap>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_SelectStage, ObjID::OBJ_SELECTSTAGE);

	if (SelectMapBGMOnOff == false)
	{
		SelectMapBGMOnOff = true;
		CSoundMgr::GetInstance()->PlaySoundW(L"Epic7_Sanctuary.mp3", CSoundMgr::CHANNEL_ID::BGM_SelectMap);
	}
	CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM_SelectMap, 0);

}

void CSSelectStage::Update()
{
}

void CSSelectStage::LateUpdate()
{
}

void CSSelectStage::Render(HDC hdc)
{

}

void CSSelectStage::Release()
{
	CObjMgr::GetInstance()->Release();
}