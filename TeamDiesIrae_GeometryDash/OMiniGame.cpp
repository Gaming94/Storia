#include "stdafx.h"

#include "OAlponso.h"
#include "OLeo.h"
#include "OAlponso_Illust.h"

#include "OMiniGame.h"


COMiniGame::COMiniGame()
	:TotalPieceCnt(9), ShakeCnt(0), MyPosition(2)
{
	PieceX = 215;
	PieceY = 268;
}


COMiniGame::~COMiniGame()
{
}

void COMiniGame::Init()
{
	CBMPMgr::GetInstance()->InsertBackGroundBmp(L"../Image/BackGround/RocoTown/BackGround_Size.bmp", L"BackGround_Size");

	//알폰소
	pSellect_Alponso = AbstractFactory<COAlponso>::CreateObj(-50, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Alponso, ObjID::OBJ_CHARACTER);

	//레오
	pSellect_Leo = AbstractFactory<COLeo>::CreateObj(WINCX+100, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Leo, ObjID::OBJ_CHARACTER);
}

void COMiniGame::LateInit()
{

}

int COMiniGame::Update()
{
	if (TotalPieceCnt >= 1)
	{
		CObj* pSellect_Piece = AbstractFactory<COAlponso_Illust>::CreateObj(500+(PieceX + 5) * CntX, 100+(PieceY + 5) * CntY);
		CObjMgr::GetInstance()->AddObject(pSellect_Piece, ObjID::OBJ_CHARACTER);
		m_PiecePuzzle.insert(pair<int, CObj*>(PieceNumber, pSellect_Piece));

		pSellect_Piece->SetIsPuzzle(true);
		pSellect_Piece->SetPuzzleNum(PieceNumber);

		pSellect_Piece->SetXCnt(CntX);
		pSellect_Piece->SetYCnt(CntY);

		CntX++;
		if (CntX == MaxCntX && CntY != MaxCntY)
		{
			CntX = 0;
			CntY++;
		}
		PieceNumber++;
		TotalPieceCnt--;
	}



	if (pSellect_Alponso->GetInfo().FX >= WINCX + 100)
	{
		pSellect_Alponso->SetPos(-100, pSellect_Alponso->GetInfo().FY);
	}
	if (pSellect_Leo->GetInfo().FX <= -100)
	{
		pSellect_Leo->SetPos(WINCX + 100, pSellect_Leo->GetInfo().FY);
	}

	return 0;
}

void COMiniGame::LateUpdate()
{
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	for (Iter = m_PiecePuzzle.begin(); Iter != m_PiecePuzzle.end(); Iter++)
	{
		rt[Iter->first] = Iter->second->GetRect();
	}



	//if (PtInRect(&rt[0], pt))
	//{
		if (CKeyMgr::GetInstance()->KeyDown(VK_UP))
		{
			ScreenShake = true;
			//for (Iter = m_PiecePuzzle.begin(); Iter != m_PiecePuzzle.end(); Iter++)
			//{
			//	if (Iter->first == 8)
			//	{
			//		Iter->second->SetPos(Iter->second->GetInfo().FX, Iter->second->GetInfo().FY - PieceY - 5);
			//	}
			//}
		}

		if (CKeyMgr::GetInstance()->KeyDown(VK_DOWN))
		{
			ScreenShake = true;
			//for (Iter = m_PiecePuzzle.begin(); Iter != m_PiecePuzzle.end(); Iter++)
			//{
			//	if (Iter->first == 8)
			//	{
			//		Iter->second->SetPos(Iter->second->GetInfo().FX, Iter->second->GetInfo().FY + PieceY + 5);
			//	}
			//}
		}

		if (CKeyMgr::GetInstance()->KeyDown(VK_RIGHT))
		{
			ScreenShake = true;
			MyDest = MyPosition + 1;

			//Iter = m_PiecePuzzle.begin();
			//for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
			//{
			//	if (Iter->second->GetPuzzleNum() == MyPosition)
			//	{
			//		if (Iter->second->GetCntX() == 2)
			//		{
			//			ChangeSwitch = false;
			//		}
			//		else
			//		{
			//		}
			//	}
			//}

			if (ChangeSwitch == true)
			{
				Iter = m_PiecePuzzle.begin();
				for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				{
					if (Iter->second->GetPuzzleNum() == MyPosition)
					{
						Iter->second->SetPos((Iter)->second->GetInfo().FX + PieceX + 5, (Iter)->second->GetInfo().FY);
					}

					if (Iter->second->GetPuzzleNum() == MyDest)
					{
						Iter->second->SetPos((Iter)->second->GetInfo().FX - PieceX - 5, (Iter)->second->GetInfo().FY);
					}
				}

				Iter = m_PiecePuzzle.begin();
				for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				{
					if (Iter->second->GetPuzzleNum() == MyPosition)
					{
						(Iter)->second->SetPuzzleNum(Iter->second->GetPuzzleNum() - 1);
						(++Iter)->second->SetPuzzleNum(Iter->second->GetPuzzleNum() + 1);
					}
				}
			}

			if (ChangeSwitch == true)
			{
				MyPosition++;
				ChangeSwitch = false;
			}
		}


		if (CKeyMgr::GetInstance()->KeyDown(VK_LEFT))
		{
			ScreenShake = true;
			MyDest = MyPosition - 1;

			Iter = m_PiecePuzzle.begin();
			for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
			{
				//if (Iter->second->GetPuzzleNum() == MyPosition)
				//{
				//	if (Iter->second->GetCntX() == 0)
				//	{
				//		ChangeSwitch = false;
				//	}
				//	else
				//	{
				//	}
				//}
				ChangeSwitch = true;
			}

			if (ChangeSwitch == true)
			{
				//Iter = m_PiecePuzzle.begin();
				//for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				//{
				//	if (Iter->second->GetPuzzleNum() == MyPosition)
				//	{
				//		ChangePuzzle(&(Iter->second), &((--Iter)->second));
				//		break;
				//	}
				//}

				Iter = m_PiecePuzzle.begin();
				for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				{
				
					if (Iter->second->GetPuzzleNum() == MyDest)
					{
						Iter->second->SetPos((Iter)->second->GetInfo().FX + PieceX + 5, (Iter)->second->GetInfo().FY);
					}
				
					if (Iter->second->GetPuzzleNum() == MyPosition)
					{
						Iter->second->SetPos((Iter)->second->GetInfo().FX - PieceX - 5, (Iter)->second->GetInfo().FY);
					}
				}
				
				//Iter = m_PiecePuzzle.begin();
				//for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				//{
				//	if (Iter->second->GetPuzzleNum() == MyDest)
				//	{
				//		int TempCntX;
				//		TempCntX = Iter->second->GetCntX();
				//		Iter->second->SetXCnt((++Iter)->second->GetCntX());
				//		(Iter++)->second->SetXCnt(TempCntX);
				//	}
				//}
				
				Iter = m_PiecePuzzle.begin();
				for (Iter; Iter != m_PiecePuzzle.end(); Iter++)
				{
					if (Iter->second->GetPuzzleNum() == MyDest)
					{
						(Iter++)->second->SetPuzzleNum((Iter)->second->GetPuzzleNum() + 1);
						Iter->second->SetPuzzleNum(Iter->second->GetPuzzleNum() - 1);
					}
				}
			}

			if (ChangeSwitch == true)
			{
				MyPosition--;
				ChangeSwitch = false;
			}
		}

		if (ScreenShake == true)
		{
			m_SwiftX = rand() % 7;
			m_SwiftY = rand() % 7;
			ShakeCnt++;
		}

		if (ScreenShake == true)
		{
			if (ShakeCnt >= 20)
			{
				ScreenShake = false;
				m_SwiftX = 0;
				m_SwiftY = 0;
				ShakeCnt = 0;
			}
		}

		pSellect_Leo->BeNpc_Walking();
		pSellect_Alponso->MoveTo(1);
		pSellect_Leo->MoveTo(0);
}

void COMiniGame::Render(HDC hdc)
{
	HDC hMemDC = nullptr;

	NULL_CHECK(hMemDC = CBMPMgr::GetInstance()->FindBackGroundImage(L"BackGround_Size"));
	BitBlt(hdc, 0 + m_SwiftX, 0 + m_SwiftY, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void COMiniGame::Release()
{
}
