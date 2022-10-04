#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"
#include "OCookie.h"

#include "OMarket.h"

#include "OSanctuary.h"

COSanctuary::COSanctuary()
	:IsStageStart(0), isGoto(0)
{
	ScrollMax = 500;
}

COSanctuary::~COSanctuary()
{
	Release();
}

void COSanctuary::Init()
{
	switch (SelectCharacterNumber)
	{
		case eChar_Num::ALPONSO:
		{
			pSellect_Player = AbstractFactory<COAlponso>::CreateObj(-100, 750, true);
		}
		break;

		case eChar_Num::LEO:
		{
			pSellect_Player = AbstractFactory<COLeo>::CreateObj(-100, 750, true);
		}
		break;
	}

	pSellect_NPC = AbstractFactory<COCookie>::CreateObj(950, 720);
	CObjMgr::GetInstance()->AddObject(pSellect_NPC, ObjID::OBJ_CHARACTER);
	pSellect_NPC->SetIsBattle(false);

	CObjMgr::GetInstance()->AddObject(pSellect_Player, ObjID::OBJ_CHARACTER);
	pSellect_Player->SetIsBattle(false);

	pSellect_NPC->SetTarget(pSellect_Player);

	CloseRect = { 1150, 200, 1200, 250 };
	BuyPotionRect = { 320, 370, 401, 400 };
	BuyClubRect = { 450, 370, 521, 400 };
	BuyHammerRect1 = { 550, 370, 621, 400 };
	BuyHammerRect2 = { 320, 540, 401, 570 };
	BuyGloveRect = { 420, 540, 501, 570 };
}

void COSanctuary::LateInit()
{
}

int COSanctuary::Update()
{
	if (IsStageStart == false)
	{
		//스테이지 시작전 맵 한번 보여주기
		if (isGoto == false)
		{
			if (Scroll <= ScrollMax)
			{
				Scroll += 5;
				pSellect_NPC->SetPos(pSellect_NPC->GetInfo().FX - 5, pSellect_NPC->GetInfo().FY);
			}

			if (Scroll >= ScrollMax)
				isGoto = true;
		}
		else
		{
			if (Scroll >= 1)
			{
				Scroll -= 5;
				pSellect_NPC->SetPos(pSellect_NPC->GetInfo().FX + 5, pSellect_NPC->GetInfo().FY);
			}
		
			if (Scroll <= 1)
			{
				IsStageStart = true;
			}
		}

		
	}

	if (IsStageStart == true)
	{
		pSellect_Player->MoveTutorial(5);
	}
	

	//스테이지를 클리어했을때 맵 스크롤링가능
	if (StageClear == true)
	{
		ScrollingFnc();
	}

	return 0;
}

void COSanctuary::LateUpdate()
{
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	CookieRect = pSellect_NPC->GetRect();
	
	

	if (PtInRect(&CookieRect, pt))
	{
		if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON) && IsMarketOnOff == false)
		{
			//상점 열림
			IsMarketOnOff = true;
			pSellect_Market = AbstractFactory<COMarket>::CreateObj(700, -500);
			CObjMgr::GetInstance()->AddObject(pSellect_Market, ObjID::OBJ_UI);
			pSellect_Market->SetTarget(pSellect_Player);

			pSellect_DummyPlayer = AbstractFactory<COLeo>::CreateObj(950, 500, false);
			CObjMgr::GetInstance()->AddObject(pSellect_DummyPlayer, ObjID::OBJ_CHARACTER2);
			pSellect_DummyPlayer->SetLR(false);
			pSellect_DummyPlayer->BeNpc_Standing();

			CSoundMgr::GetInstance()->PlaySoundW(L"MarketOpen.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
			CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
		}
	}

	if (IsMarketOnOff == true)
	{
		//상점닫기
		if (PtInRect(&CloseRect, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Market->SetDead();
				pSellect_DummyPlayer->SetDead();
				IsMarketOnOff = false;
			}
		}

		//포션구입
		if (PtInRect(&BuyPotionRect, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Player->SetPlayerPotion();
				pSellect_Player->SetPlayerMoney(0, 10);

				CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
				CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
			}
		}

		//나무몽둥이 구입
		if (PtInRect(&BuyClubRect, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Player->SetPlayerWeapon(1);
				pSellect_Player->SetPlayerMoney(0, 100);

				CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
				CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
			}
		}

		//망치 구입1
		if (PtInRect(&BuyHammerRect1, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Player->SetPlayerWeapon(2);
				pSellect_Player->SetPlayerMoney(0, 150);

				CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
				CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
			}
		}

		//망치 구입2
		if (PtInRect(&BuyHammerRect2, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Player->SetPlayerWeapon(2);
				pSellect_Player->SetPlayerMoney(0, 150);

				CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
				CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
			}
		}

		//글러브
		if (PtInRect(&BuyGloveRect, pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
			{
				pSellect_Player->SetPlayerWeapon(3);
				pSellect_Player->SetPlayerMoney(0, 200);

				CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3", CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
				CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
			}
		}
	}


	if (StageClear == true)
	{
		if (pSellect_Player->GetInfo().FX >= WINCX)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
		}
	}
}

void COSanctuary::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Sanctuary"));
	BitBlt(hdc, 0 + m_SwiftX, 0 + m_SwiftY, WINCX, WINCY, hMemDC, 0 + Scroll, 0, SRCCOPY);
}

void COSanctuary::Release()
{
}

void COSanctuary::ScrollingFnc()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		if (pSellect_Player->GetInfo().FX >= 845)
		{
			if (Scroll <= ScrollMax)
			{
				Scrolling = true;
				Scroll += 5;
				pSellect_NPC->SetPos(pSellect_NPC->GetInfo().FX - 5, pSellect_NPC->GetInfo().FY);
			}
			else
			{
				Scrolling = false;
			}
		}
	}

	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		if (pSellect_Player->GetInfo().FX <= 845)
		{
			if (Scroll >= 1)
			{
				Scrolling = true;
				Scroll -= 5;
				pSellect_NPC->SetPos(pSellect_NPC->GetInfo().FX + 5, pSellect_NPC->GetInfo().FY);
			}
			else
			{
				Scrolling = false;
			}
		}
	}

	if (Scrolling == true)
	{
		pSellect_Player->SetPlayerSpeed(0);
	}
	else
	{
		pSellect_Player->SetPlayerSpeed(5);
	}

	if (CKeyMgr::GetInstance()->KeyUp(VK_RIGHT) || CKeyMgr::GetInstance()->KeyUp(VK_LEFT))
	{
		Scrolling = false;
		pSellect_Player->SetPlayerSpeed(5);
	}
}
