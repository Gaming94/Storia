#include "stdafx.h"

#include "OSelectCharacter.h"

#include "SSelectCharacter.h"


CSSelectCharacter::CSSelectCharacter()
{
}


CSSelectCharacter::~CSSelectCharacter()
{
	Release();
}

void CSSelectCharacter::Init()
{
	// 캐릭터 선택 창의 배경이미지를 추가합니다
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/CharacterSelect/BackGround_CharSelect2.bmp", L"BackGround_CharSelect");

	// 추상팩토리 방식으로 씬 오브젝트 추가합니다
	pSellect_SelectCharacter = AbstractFactory<COSelectCharacter>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_SelectCharacter, ObjID::OBJ_SELECTCHARACTER);

	// 캐릭터 재선택으로 인한 사운드 겹침현상 방지
	if (SelectCharBGMOnOff == false)
	{
		CSoundMgr::GetInstance()->PlaySoundW(L"Moonlight_BGM.mp3", CSoundMgr::CHANNEL_ID::BGM);
		CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.3);

		SelectCharBGMOnOff = true;
	}
}

void CSSelectCharacter::Update()
{
}

void CSSelectCharacter::LateUpdate()
{
	
}

void CSSelectCharacter::Render(HDC hdc)
{

}

void CSSelectCharacter::Release()
{
	CObjMgr::GetInstance()->Release();
}
