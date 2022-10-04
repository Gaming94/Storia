#include "stdafx.h"

#include "OTutorial.h"

#include "STutorial.h"


CSTutorial::CSTutorial()
{
}


CSTutorial::~CSTutorial()
{
	Release();
}

void CSTutorial::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Tutorial/Tutorial_Field.bmp", L"Tutorial_Field");
	
	pSellect_Tutorial = AbstractFactory<COTutorial>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Tutorial, ObjID::OBJ_TUTORIAL);
}

void CSTutorial::Update()
{
}

void CSTutorial::LateUpdate()
{
}

void CSTutorial::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Tutorial_Field"));
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CSTutorial::Release()
{
	CObjMgr::GetInstance()->Release();
}
