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
	// ĳ���� ���� â�� ����̹����� �߰��մϴ�
	CBMPMgr::GetInstance()->InsertImg(L"../Image/BackGround/CharacterSelect/BackGround_CharSelect2.bmp", L"BackGround_CharSelect");

	// �߻����丮 ������� �� ������Ʈ �߰��մϴ�
	pSellect_SelectCharacter = AbstractFactory<COSelectCharacter>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_SelectCharacter, ObjID::OBJ_SELECTCHARACTER);

	// ĳ���� �缱������ ���� ���� ��ħ���� ����
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
