#include "stdafx.h"

//캐릭터
#include "OAlphaEffect.h"
#include "OAlponso.h"
#include "OLeo.h"

//텍스트박스
#include "OTextBox.h"

#include "OSelectCharacter.h"


COSelectCharacter::COSelectCharacter()
{
}


COSelectCharacter::~COSelectCharacter()
{
	Release();
}

void COSelectCharacter::Init()
{
	LodingShadow = true;

	//알파블렌딩 이펙트
	if (BACKtoReturn == false)
	{
		pSellect_AlphaEffect = AbstractFactory<COAlphaEffect>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_AlphaEffect, ObjID::OBJ_ALPHAEFFECT);
		pSellect_AlphaEffect->SetFadeinout(0);
	}

	//알폰소
	pSellect_Alponso = AbstractFactory<COAlponso>::CreateObj(-50, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Alponso, ObjID::OBJ_CHARACTER);
	
	//레오
	pSellect_Leo = AbstractFactory<COLeo>::CreateObj(-300, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Leo, ObjID::OBJ_CHARACTER);
}

void COSelectCharacter::LateInit()
{
	
}

int COSelectCharacter::Update()
{
	if (BACKtoReturn == false)
	{
		if (IsStart == true)
		{
			pSellect_Alponso->MoveSelectCharacter(5, 500);
			pSellect_Leo->MoveSelectCharacter(5, 1100);

			if (pSellect_Alponso->GetInfo().FX >= 500)
			{
				pSellect_Alponso->BeNpc_Standing();
				pSellect_Alponso->SetLR(false);
			}

			if (pSellect_Leo->GetInfo().FX >= 1100)
			{
				pSellect_Leo->BeNpc_Standing();
				pSellect_Leo->SetLR(true);
			}
		}
	}
	else
	{
		IsStart = true;
		pSellect_Alponso->SetPos(500, 700);
		pSellect_Leo->SetPos(1100, 700);
	}

	return 0;
}

void COSelectCharacter::LateUpdate()
{
	if (IsStart == true)
	{
		pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		AlponsoRect = pSellect_Alponso->GetRect();
		LeoRect = pSellect_Leo->GetRect();

		// 마우스 포인터가 첫번째 캐릭터 Rect 영역에 위치할 때
		if (PtInRect(&AlponsoRect, pt))
		{
			// 마우스 왼쪽버튼이 눌렸을 경우
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				// 캐릭터의 default값을 잡아줍니다
				SelectCharacterNumber = eChar_Num::ALPONSO;
				CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_TUTORIAL);
			}
		}

		// 마우스 포인터가 두번째 캐릭터 Rect 영역에 위치할 때
		if (PtInRect(&LeoRect, pt))
		{
			// 마우스 왼쪽버튼이 눌렸을 경우
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				// 캐릭터의 default값을 잡아줍니다
				SelectCharacterNumber = eChar_Num::LEO;
				CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_TUTORIAL);
			}
		}
	}

	if (BACKtoReturn == false)
	{
		if (DummyAlphaCnt <= 255)
		{
			DummyAlphaCnt += 5;

			if (DummyAlphaCnt == 255)
			{
				pSellect_AlphaEffect->SetDead();
				IsStart = true;
			}
		}
	}
}

void COSelectCharacter::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"BackGround_CharSelect"));
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void COSelectCharacter::Release()
{
	
}
