#include "stdafx.h"

#include "OText.h"
#include "OAlponso_Illust.h"
#include "OLeo_Illust.h"

#include "OTextBox.h"


COTextBox::COTextBox()
{
}


COTextBox::~COTextBox()
{
	Release();
}

void COTextBox::Init()
{
	CBMPMgr::GetInstance()->InsertImg(L"../Image/TextBox/TextBox.bmp", L"TextBox");

	m_tInfo.FX = 0;
	m_tInfo.FY = 0;

	m_tInfo.FCX = CBMPMgr::GetInstance()->FindImg_SizeX(L"TextBox", L"../Image/TextBox/TextBox.bmp");
	m_tInfo.FCY = CBMPMgr::GetInstance()->FindImg_SizeY(L"TextBox", L"../Image/TextBox/TextBox.bmp");

	pSellect_Text = AbstractFactory<COText>::CreateObj(m_tInfo.FX, m_tInfo.FY, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Text, ObjID::OBJ_TEXT);

	pSellect_Teller_Alponso = AbstractFactory<COAlponso_Illust>::CreateObj(100 , 50, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Teller_Alponso, ObjID::OBJ_CHARILLUST);

	pSellect_Teller_Leo = AbstractFactory<COLeo_Illust>::CreateObj(100, 50, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Teller_Leo, ObjID::OBJ_CHARILLUST);

	ZeroMemory(&blend, sizeof(blend));
}

void COTextBox::LateInit()
{
}

int COTextBox::Update()
{
	//챕터넘버 전달
	pSellect_Text->SetChapterNumber(ChapterNumber);

	//누구 이미지 처리할지
	switch (WhoIsTeller)
	{
	case eChar_Num::ALPONSO:
		pSellect_Teller_Alponso->SetIsTeller(true);
		pSellect_Teller_Leo->SetIsTeller(false);
		pSellect_Text->SetTextOnOff(true);
		break;
	case eChar_Num::LEO:
		pSellect_Teller_Leo->SetIsTeller(true);
		pSellect_Teller_Alponso->SetIsTeller(false);
		pSellect_Text->SetTextOnOff(true);
		break;
	case 3:
		break;
	}

	if (ChapterNumber == 1 && TextNumber == 8)
	{
		pSellect_Teller_Alponso->SetDead();
		pSellect_Teller_Leo->SetDead();
	}

	//텍스트 오픈
	pSellect_Text->SetWhoIsTeller(WhoIsTeller);
	pSellect_Text->SetTextNumber(TextNumber);

	//pSellect_Text->SetIsTeller(true);

	//텍스트박스 닫음
	if (m_bIsDead == true)
	{
		pSellect_Text->SetDead();

		return DEAD_EVENT;
	}

	return 0;
}

void COTextBox::LateUpdate()
{
	
}

void COTextBox::Render(HDC hdc)
{
	HDC hMemDC = nullptr;
	//blend.BlendFlags = 0;
	//blend.BlendOp = 0;
	//blend.AlphaFormat = AC_SRC_OVER;
	//blend.SourceConstantAlpha = 254;

	if (m_TextBoxTF == true)
	{
		NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindImg(L"TextBox"));
		GdiTransparentBlt(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, RGB(181, 230, 29));
		//GdiAlphaBlend(hdc, m_tInfo.FX, m_tInfo.FY, m_tInfo.FCX, m_tInfo.FCY, hMemDC, 0, 0, m_tInfo.FCX, m_tInfo.FCY, blend);
	
	}
}

void COTextBox::Release()
{
}
