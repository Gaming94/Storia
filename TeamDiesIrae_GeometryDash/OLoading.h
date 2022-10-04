#pragma once
#include "Obj.h"
class COLoading :
	public CObj
{
public:
	COLoading();
	~COLoading();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	//Dummy
	int LoadingBarCnt = 0;
	int LoadingBarCntr = WINCX;

	int		RGBCnt = 0;

	int		TextCnt = 3;
	float	LoadingCnt;
	wchar_t* WLoadingCnt;
	WCHAR WLoadingCntCpy[5];

	bool	PressAnyKeySwitch = 0;
	bool	LikeAlphaTEXT;
	int		PressAnyKeyCnt = 0;

	CObj* pSellect_Character;
};

