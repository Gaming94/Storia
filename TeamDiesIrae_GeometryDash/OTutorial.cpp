#include "stdafx.h"
#include "OTutorial.h"

#include "OAlponso.h"
#include "OLeo.h"

#include "OAttentionMark.h"

#include "OSkillBox.h"
#include "OTextBox.h"

#include "OTutorialBlObj.h"
#include "OTutorialBlObj2.h"

COTutorial::COTutorial()
	:m_TextNumber(0), StoryComplete(0)
{
}


COTutorial::~COTutorial()
{
	Release();
}

void COTutorial::Init()
{
	switch(SelectCharacterNumber)
	{
		case eChar_Num::ALPONSO:
		{
			pSellect_Player = AbstractFactory<COAlponso>::CreateObj(-100, 700, true);
			CObjMgr::GetInstance()->AddObject(pSellect_Player, ObjID::OBJ_CHARACTER);

			pSellect_NPC = AbstractFactory<COLeo>::CreateObj(750, 600, false);
			CObjMgr::GetInstance()->AddObject(pSellect_NPC, ObjID::OBJ_NPC);

			WhoIsTeller = 2;
		}
		break;

		case eChar_Num::LEO:
		{
			pSellect_Player = AbstractFactory<COLeo>::CreateObj(-100, 700, true);
			CObjMgr::GetInstance()->AddObject(pSellect_Player, ObjID::OBJ_CHARACTER);

			pSellect_NPC = AbstractFactory<COAlponso>::CreateObj(750, 600, false);
			CObjMgr::GetInstance()->AddObject(pSellect_NPC, ObjID::OBJ_NPC);

			WhoIsTeller = 1;
		}
		break;
	}
	pSellect_BlendObj1 = AbstractFactory<COTutorialBlObj>::CreateObj(80, 592);
	CObjMgr::GetInstance()->AddObject(pSellect_BlendObj1, ObjID::OBJ_BLENDOBJ);

	pSellect_BlendObj2 = AbstractFactory<COTutorialBlObj2>::CreateObj(961, 520);
	CObjMgr::GetInstance()->AddObject(pSellect_BlendObj2, ObjID::OBJ_BLENDOBJ);

	pSellect_TextBox = AbstractFactory<COTextBox>::CreateObj(200, 710, false);
	CObjMgr::GetInstance()->AddObject(pSellect_TextBox, ObjID::OBJ_TEXTBOX);

	pSellect_AttentionMark = AbstractFactory<COAttentionMark>::CreateObj(750, 450);
	CObjMgr::GetInstance()->AddObject(pSellect_AttentionMark, ObjID::OBJ_TEXTBOX);
}

void COTutorial::LateInit()
{
}

int COTutorial::Update()
{
	pSellect_NPC->BeNpc_Standing();

	if (MoveComplete == false)
	{
		pSellect_Player->MoveTutorial(5);

		if (pSellect_Player->GetInfo().FX >= 300)
		{
			MoveComplete = true;
		}
	}

	if (pSellect_NPC->GetInfo().FX >= pSellect_Player->GetInfo().FX)
	{
		pSellect_NPC->SetLR(false);
	}
	if (pSellect_NPC->GetInfo().FX <= pSellect_Player->GetInfo().FX)
	{
		pSellect_NPC->SetLR(true);
	}


	if (pSellect_Player->GetInfo().FX >= 1500)
	{
		pSellect_Player->SetPos(1500, pSellect_Player->GetInfo().FY);
	}

	//블렌딩 연습
	if (pSellect_Player->GetInfo().FX >= 20 && pSellect_Player->GetInfo().FX <= 170 && pSellect_Player->GetInfo().FY >= 650)
		pSellect_BlendObj1->SetBlendOnOff(true);
	else
		pSellect_BlendObj1->SetBlendOnOff(false);


	if (pSellect_Player->GetInfo().FX >= 800 && pSellect_Player->GetInfo().FX <= 1200 && pSellect_Player->GetInfo().FY >= 590)
		pSellect_BlendObj2->SetBlendOnOff(true);
	else
		pSellect_BlendObj2->SetBlendOnOff(false);


	//이게 왜 LateUpdate로 가면 터질까
	if (fabs(pSellect_NPC->GetInfo().FX - pSellect_Player->GetInfo().FX) <= pSellect_Player->GetInfo().FCX &&
		fabs(pSellect_NPC->GetInfo().FY - pSellect_Player->GetInfo().FY) <= pSellect_Player->GetInfo().FCY / 2)
	{
		StoryStart = true;
	}

	return 0;
}

void COTutorial::LateUpdate()
{
	if (StoryStart == true)
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
		{
			m_TextNumber++;

			if (TextBoxOnOff == false)
				TextBoxOnOff = true;

			if (m_TextNumber == 10)
			{
				TextBoxOnOff = false;
				m_TextNumber = 0;
				pSellect_TextBox->SetDead();
				pSellect_AttentionMark->SetDead();
				StoryComplete = true;
			}

			if (TextBoxOnOff == true)
			{
				pSellect_TextBox->SetTextBoxTF(TextBoxOnOff);
				pSellect_TextBox->SetChapterNumber(1);
				pSellect_TextBox->SetTextNumber(m_TextNumber);

				switch (WhoIsTeller)
				{
				case eChar_Num::ALPONSO:
					pSellect_TextBox->SetWhoIsTeller(eChar_Num::ALPONSO);
					break;
				case eChar_Num::LEO:
					pSellect_TextBox->SetWhoIsTeller(eChar_Num::LEO);
					break;
				}
			}

			//변해야함 -> 정보를 주는형식으로
			if (WhoIsTeller == eChar_Num::ALPONSO)
			{
				WhoIsTeller = eChar_Num::LEO;
			}
			else if (WhoIsTeller == eChar_Num::LEO)
			{
				WhoIsTeller = eChar_Num::ALPONSO;
			}
		}
	}
	//if (CKeyMgr::GetInstance()->KeyDown(VK_BACK))
	if (pSellect_Player->GetInfo().FX <= 0 && MoveComplete == true)
	{
		BACKtoReturn = true;
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTCHARACTER);
	}

	if (CKeyMgr::GetInstance()->KeyDown('A'))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_SELECTSTAGE);
	}
}

void COTutorial::Render(HDC hdc)
{
}

void COTutorial::Release()
{
}
