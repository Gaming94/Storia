#include "stdafx.h"
#include "OMarket.h"

COMarket::COMarket()
{

}

COMarket::~COMarket()
{
	Release();
}

void COMarket::Init()
{
	//마켓 창
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Market/St_M_Practice2.bmp", L"Market_Practice");

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"Market_Practice", L"../Image/Market/St_M_Practice2.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"Market_Practice", L"../Image/Market/St_M_Practice2.bmp");

	//아이템 아이콘
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Market/Item_Club.bmp", L"Item_Club"); // 107 * 102
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Market/Item_Hammer.bmp", L"Item_Hammer"); // 107 * 102
	CBMPMgr::GetInstance()->InsertImg(L"../Image/Market/Item_Glove.bmp", L"Item_Glove"); // 107 * 102
}

void COMarket::LateInit()
{
	CObj::UpdateRect();
}

int COMarket::Update()
{
	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}

	return 0;
}

void COMarket::LateUpdate()
{
	PlayerAtk = pTarget->GetStatus().Atk;
	PlayerDef = pTarget->GetStatus().Def;
	PlayerPotion = pTarget->GetStatus().Potion;
	PlayerMoney = pTarget->GetStatus().Money;
	PlayerHp = pTarget->GetStatus().MAX_HP;


	//포션 갯수
	wPotionCnt = new wchar_t;
	_itow((int)PlayerPotion, wPotionCnt, 10);
	wcscpy_s(WLPotionCnt, sizeof(wPotionCnt), wPotionCnt);

	if (PlayerPotion >= 10)
	{
		PotionCnt = 2;
	}

	if (CKeyMgr::GetInstance()->KeyPressing(MK_RBUTTON))
	{
		ItemOn = true;
	}
	else
	{
		ItemOn = false;
	}

	//플레이어 돈
	wMoneyCnt = new wchar_t;
	_itow((int)PlayerMoney, wMoneyCnt, 10);
	wcscpy_s(WLMoneyCnt, sizeof(wMoneyCnt), wMoneyCnt);

	//플레이어 공격력
	wPlayerAtk = new wchar_t;
	_itow((int)PlayerAtk, wPlayerAtk, 10);
	wcscpy_s(WLPlayerAtk, sizeof(wPlayerAtk), wPlayerAtk);

	//플레이어 Hp
	wPlayerHP = new wchar_t;
	_itow((int)PlayerHp, wPlayerHP, 10);
	wcscpy_s(WLPlayerHP, sizeof(wPlayerHP), wPlayerHP);

	//플레이어 방어력
	wPlayerDef = new wchar_t;
	_itow((int)PlayerDef, wPlayerDef, 10);
	wcscpy_s(WLPlayerDef, sizeof(wPlayerDef), wPlayerDef);
}

void COMarket::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Market_Practice"));

	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.bottom, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 128, 0));
	//GdiTransparentBlt(hdc, 0, 0, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(0, 0, 0));

	if (pTarget->GetStatus().Weapon == 1)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Item_Club"));
		GdiTransparentBlt(hdc, 1086, 492, 65, 65, hMemDC, 0, 0, 65, 65, RGB(255, 255, 255));

		//인벤토리 무기 수치 설명
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 1080, 573, L"공격력 +10", 7);
	}
	else if (pTarget->GetStatus().Weapon == 2)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Item_Hammer"));
		GdiTransparentBlt(hdc, 1086, 492, 65, 65, hMemDC, 0, 0, 65, 65, RGB(255, 255, 255));

		//인벤토리 무기 수치 설명
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 1080, 573, L"공격력 +15", 7);
	}
	else if (pTarget->GetStatus().Weapon == 3)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"Item_Glove"));
		GdiTransparentBlt(hdc, 1086, 492, 65, 65, hMemDC, 0, 0, 65, 65, RGB(255, 255, 255));

		//인벤토리 무기 수치 설명
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 1080, 573, L"공격력 +20", 7);
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, 355, 371, L"10", 2);
	TextOut(hdc, 470, 371, L"100", 3);
	TextOut(hdc, 590, 371, L"150", 3);
	TextOut(hdc, 350, 546, L"150", 3);
	TextOut(hdc, 470, 546, L"250", 3);

	//상점 아이템 설명
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 440, 343, L"공격력 +10", 7);
	TextOut(hdc, 560, 343, L"공격력 +15", 7);
	TextOut(hdc, 320, 518, L"공격력 +15", 7);
	TextOut(hdc, 440, 518, L"공격력 +20", 7);

	//인벤토리 갯수 표시
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 900, 660, WLMoneyCnt, MoneyCnt);
	TextOut(hdc, 975, 695, WLPotionCnt, PotionCnt);

	//스테이터스 표기
	TextOut(hdc, 940, 732, WLPlayerHP, 3);
	TextOut(hdc, 945, 760, WLPlayerAtk, 2);
	TextOut(hdc, 953, 786, WLPlayerDef, 1);
}

void COMarket::Release()
{
}
