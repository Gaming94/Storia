#pragma once
#include "Obj.h"
class COMiniGame :
	public CObj
{
public:
	COMiniGame();
	~COMiniGame();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	POINT pt;
	RECT rt[9];
	RECT Practice_Rect;

	CObj* pSellect_Alponso;
	CObj* pSellect_Leo;
	CObj* pSellect_Piece;

	int TotalPieceCnt;
	int PieceNumber;

	map<int, CObj*>	m_PiecePuzzle;
	map<int, CObj*>::iterator Iter;

	int PieceX;
	int PieceY;

	bool ChangeSwitch = false;

	//shake
	bool	ScreenShake;
	int		ShakeCnt;
	int		Count = 0;

	int		m_SwiftX;
	int		m_SwiftY;

	int		MyPosition;
	int		MyDest;
};

