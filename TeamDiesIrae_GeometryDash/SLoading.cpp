#include "stdafx.h"

#include "OLoading.h"

#include "SLoading.h"


CSLoading::CSLoading()
{
}


CSLoading::~CSLoading()
{
	Release();
}

void CSLoading::Init()
{
	pSellect_Loading = AbstractFactory<COLoading>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_Loading, ObjID::OBJ_LOADING);
}

void CSLoading::Update()
{
}

void CSLoading::LateUpdate()
{
}

void CSLoading::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINCX, WINCY, NULL);
}

void CSLoading::Release()
{
	CObjMgr::GetInstance()->Release();
}
