#include "stdafx.h"

#include "ORocoTown.h"

#include "SRocoTown.h"

CSRocoTown::CSRocoTown()
{
}


CSRocoTown::~CSRocoTown()
{
	Release();
}

void CSRocoTown::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/RocoTown/RocoTown.bmp", L"RocoTown");

	CObj* pSellect_RocoTown = AbstractFactory<CORocoTown>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_RocoTown, ObjID::OBJ_ROCOTOWN);
}

void CSRocoTown::Update()
{
}

void CSRocoTown::LateUpdate()
{
}

void CSRocoTown::Render(HDC hdc)
{
}

void CSRocoTown::Release()
{
	CObjMgr::GetInstance()->Release();
}
