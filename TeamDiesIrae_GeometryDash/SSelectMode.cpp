#include "stdafx.h"

#include "OSelectMode.h"

#include "SSelectMode.h"


CSSelectMode::CSSelectMode()
{
}


CSSelectMode::~CSSelectMode()
{
}

void CSSelectMode::Init()
{
	CObj* pSellect_SelectMode = AbstractFactory<COSelectMode>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_SelectMode, ObjID::OBJ_SELECTMODE);
}

void CSSelectMode::Update()
{
}

void CSSelectMode::LateUpdate()
{
}

void CSSelectMode::Render(HDC hdc)
{
}

void CSSelectMode::Release()
{
}
