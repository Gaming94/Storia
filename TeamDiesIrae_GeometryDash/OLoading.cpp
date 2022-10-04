#include "stdafx.h"

#include "OAlponso.h"
#include "OAlphaEffect.h"

#include "OLoading.h"


COLoading::COLoading()
	:LoadingCnt(0)
{
}


COLoading::~COLoading()
{
	WLoadingCnt = nullptr;
	delete WLoadingCnt;

	Release();
}

void COLoading::Init()
{
	pSellect_Character = AbstractFactory<COAlponso>::CreateObj(-100, -100, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Character, ObjID::OBJ_NPC);

	pSellect_Character->BeNpc_Walking();
}

void COLoading::LateInit()
{
}

int COLoading::Update()
{
	pSellect_Character->SetPos(LoadingBarCnt, 400);

	if (LoadingCnt <= 100)
	{
		LoadingCnt+= 0.5f;
		if (LoadingCnt >= 100)
		{
			LoadingCnt = 100;
		}
	}

	if (LoadingCnt >= 100)
	{
		TextCnt = 4;
	}

	if(LoadingBarCnt >= WINCX / 2)
	{
		pSellect_Character->BeNpc_Standing();

	}

	//메모리 힙영역을 건드려서 일단 포기
	//인티저를 바꾸는 다른 함수를 찾으면 재활용
	//WLoadingCnt = new wchar_t;
	//_itow((int)LoadingCnt, WLoadingCnt, 10);
	
	//lstrcatW(WLoadingCnt, L"%");
	//wcscpy_s(WLoadingCntCpy, sizeof(WLoadingCnt) + 2, WLoadingCnt);
	
	//int Cnt = 2;
	//if (LoadingCnt >= 10 && LoadingCnt < 100)
	//	Cnt = 3;
	//else if (LoadingCnt >= 100)
	//	Cnt = 4;
	//wcscpy_s(WLoadingCntCpy, Cnt, WLoadingCnt);
	
	return 0;
}

void COLoading::LateUpdate()
{
	if (LoadingBarCnt <= WINCX / 2)
	{
		LoadingBarCnt += 4;
	}

	if (LoadingBarCntr >= WINCX / 2)
	{
		LoadingBarCntr -= 4;
	}

	if (RGBCnt <= 255)
	{
		RGBCnt++;
		if (RGBCnt >= 255)
			RGBCnt = 255;
	}

	if (PressAnyKeySwitch == true)
	{
		if (LikeAlphaTEXT == false)
		{
			PressAnyKeyCnt += 5;

			if (PressAnyKeyCnt >= 200)
				LikeAlphaTEXT = true;
		}
		else
		{
			PressAnyKeyCnt -= 5;

			if (PressAnyKeyCnt <= 0)
				LikeAlphaTEXT = false;
		}
	}


	if (LoadingBarCnt >= WINCX / 2)
	{
		PressAnyKeySwitch = true;
		if (CKeyMgr::GetInstance()->AnyKeyDown())
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTCHARACTER);
		}
	}
}

void COLoading::Render(HDC hdc)
{
	HBRUSH Brush, oldBrush;
	Rectangle(hdc, 785, 270, 905, 500);
	//Rectangle(hdc, 785, 385, 895, 595);
	//Rectangle(hdc, (WINCX / 2) - 50, (WINCY / 2)  - 50, (WINCX / 2) + 50, (WINCY / 2) + 160);

	Brush = CreateSolidBrush(RGB(10, 10, 10));
	oldBrush = (HBRUSH)SelectObject(hdc, Brush);

	Rectangle(hdc, 790, 275, 901, 495);
	//Rectangle(hdc, 791, 390, 891, 590);
	//Rectangle(hdc, (WINCX / 2) - 44, (WINCY / 2) - 45, (WINCX / 2) + 44, (WINCY / 2) + 155);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);


	HPEN Pen;
	Pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 150));
	HPEN oldPen = (HPEN)SelectObject(hdc, Pen);

	MoveToEx(hdc, 0, 500, NULL);
	LineTo(hdc, LoadingBarCnt, 500);

	MoveToEx(hdc, LoadingBarCntr, 500, NULL);
	LineTo(hdc, WINCX, 500);

	SelectObject(hdc, oldPen);
	DeleteObject(Pen);


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(PressAnyKeyCnt, PressAnyKeyCnt, PressAnyKeyCnt));
	TextOut(hdc, 796, 520, L"PressAnyKey", strlen("PressAnyKey"));
	
	//SetTextColor(hdc, RGB(255, 255, 255));
	//TextOut(hdc, 823, 367, WLoadingCntCpy, TextCnt);
	//TextOut(hdc, 843, 367, L"%", 1);
}

void COLoading::Release()
{
	
}
