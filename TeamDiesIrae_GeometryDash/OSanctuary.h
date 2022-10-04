#pragma once
#include "Obj.h"
class COSanctuary :
	public CObj
{
public:
	COSanctuary();
	~COSanctuary();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	void ScrollingFnc();

private:
	CObj*		pSellect_Player;
	CObj*		pSellect_DummyPlayer;
	CObj*		pSellect_NPC;
	CObj*		pSellect_Market;

	POINT		pt;
	RECT		CookieRect;

	//상점 버튼
	RECT		CloseRect;
	RECT		BuyPotionRect;
	RECT		BuyClubRect;
	RECT		BuyHammerRect1;
	RECT		BuyHammerRect2;
	RECT		BuyGloveRect;

	bool IsSpawn;
	bool IsMarketOnOff;

	int Max_Size = 2223;
	int Scroll = 0;

	bool Scrolling = 0;
	bool StageClear = 1;

private:
	//캐릭터 등장 전
	bool IsStageStart;

	bool isGoto;
};

