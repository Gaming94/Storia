#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"
#include "OFireCracker.h"
#include "ONumbering.h"

#include "OHorseRace.h"


COHorseRace::COHorseRace()
	:IsStageStart(0), isGoto(0)
{
	ScrollMax = 500;
	ShakeCnt = 0;

	Goal = 1600;
	Grade = 1;

	srand((unsigned)time(nullptr));
}


COHorseRace::~COHorseRace()
{
}

void COHorseRace::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/Beroia/Beroia_Racing.bmp", L"Beroia_Racing");

	pSellect_Player1 = AbstractFactory<COLeo>::CreateObj(-100, 600, true);
	CObjMgr::GetInstance()->AddObject(pSellect_Player1, ObjID::OBJ_CHARACTER);

	pSellect_Player2 = AbstractFactory<COLeo>::CreateObj(-200, 700, true);
	CObjMgr::GetInstance()->AddObject(pSellect_Player2, ObjID::OBJ_CHARACTER);

	pSellect_Player3 = AbstractFactory<COLeo>::CreateObj(-300, 800, true);
	CObjMgr::GetInstance()->AddObject(pSellect_Player3, ObjID::OBJ_CHARACTER);
}

void COHorseRace::LateInit()
{
}

int COHorseRace::Update()
{
	if (IsStageStart == false)
	{
		//스테이지 시작전 맵 한번 보여주기
		if (isGoto == false)
		{
			if (Scroll <= ScrollMax)
			{
				Scroll += 5;
			}

			if (Scroll >= ScrollMax)
				isGoto = true;
		}
		else
		{
			if (Scroll >= 1)
			{
				Scroll -= 5;
			}

			if (Scroll <= 1)
			{
				IsStageStart = true;
			}
		}
	}
	if (CKeyMgr::GetInstance()->KeyDown('A'))
	{
		pSellect_Numbering = AbstractFactory<CONumbering>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_Numbering, ObjID::OBJ_NUMBERING);
	}

	if (IsStageStart == true && isStart == false)
	{
		pSellect_Player1->MoveHorseRace(250);
		pSellect_Player2->MoveHorseRace(150);
		pSellect_Player3->MoveHorseRace(50);
	}

	if (isStart == true)
	{
		ScrollFnc();
		pSellect_Player1->MoveHorseRace(Goal);
		pSellect_Player2->MoveHorseRace(Goal - 100);
		pSellect_Player3->MoveHorseRace(Goal - 200);
	}

	if (FireCrackerSwitch == true && FireCracker == false)
	{
		pSellect_FireCracker = AbstractFactory<COFireCracker>::CreateObj(800, 165);
		CObjMgr::GetInstance()->AddObject(pSellect_FireCracker, ObjID::OBJ_MINIGAME);

		FireCracker = true;
	}

	return 0;
}

void COHorseRace::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown('A'))
		isStart = true;

	if (isStart == true)
	{
		if (dwTime + 300 < GetTickCount64())
		{
			if (Scrolling == false)
			{
				if (isRacing[0] == false)
					pSellect_Player1->SetPlayerSpeed(rand() % 5 + 2);

				if (isRacing[1] == false)
					pSellect_Player2->SetPlayerSpeed(rand() % 5 + 2);

				if (isRacing[2] == false)
					pSellect_Player3->SetPlayerSpeed(rand() % 5 + 2);
			}
			else
			{
				pSellect_Player1->SetPlayerSpeed((rand() % 2));
				pSellect_Player2->SetPlayerSpeed((rand() % 2));
				pSellect_Player3->SetPlayerSpeed((rand() % 2));
			}

			dwTime = GetTickCount64();
		}

		if (pSellect_Player1->GetInfo().FX >= Goal - 10 && isRacing[0] == false)
		{
			isRacing[0] = true;
			Rank[0] = Grade;
			if (Grade <= 3)
				Grade++;
		}

		if (pSellect_Player2->GetInfo().FX >= Goal - 110 && isRacing[1] == false)
		{
			isRacing[1] = true;
			Rank[1] = Grade;
			if (Grade <= 3)
				Grade++;
		}

		if (pSellect_Player3->GetInfo().FX >= Goal - 210 && isRacing[2] == false)
		{
			isRacing[2] = true;
			Rank[2] = Grade;
			if (Grade <= 3)
				Grade++;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (Rank[i] == 1)
		{
			switch (i)
			{
			case 0:
				pSellect_Player1->BeNpc_Attacking();
				break;
			case 1:
				pSellect_Player2->BeNpc_Attacking();
				break;
			case 2:
				pSellect_Player3->BeNpc_Attacking();
				break;
			}
		}
	}


	if (ScreenShake == true)
	{
		m_SwiftX = rand() % 7;
		m_SwiftY = rand() % 7;
		ShakeCnt++;
	}	

	if (Grade >= 3)
	{
		isStart == false;
		FireCrackerSwitch = true;
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
		Restart();
}

void COHorseRace::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"Beroia_Racing"));
	BitBlt(hdc, 0 + m_SwiftX, 0 + m_SwiftY, WINCX, WINCY, hMemDC, 0 + Scroll, 0, SRCCOPY);
}

void COHorseRace::Release()
{
}

void COHorseRace::ScrollFnc()
{
	if (pSellect_Player1->GetInfo().FX >= 845)
	{
		if (Scroll <= ScrollMax)
		{
			Scrolling = true;
			Scroll += 5;
		}
		else
		{
			Scrolling = false;
		}
	}

	if (pSellect_Player1->GetInfo().FX <= 845)
	{
		if (Scroll >= 1)
		{
			Scrolling = true;
			Scroll -= 5;
		}
		else
		{
			Scrolling = false;
		}
	}
}

void COHorseRace::Restart()
{
	pSellect_Player1->SetPos(250, 600);
	pSellect_Player1->BeNpc_Standing();

	pSellect_Player2->SetPos(150, 700);
	pSellect_Player2->BeNpc_Standing();

	pSellect_Player3->SetPos(50, 800);
	pSellect_Player3->BeNpc_Standing();

	for (int i = 0; i < 3; i++)
	{
		Rank[i] = false;
		isRacing[i] = false;
	}

	Grade = 1;

	if (isStart == false)
		isStart = true;
	else
		isStart = false;

	Scroll = 0;
}
