#pragma once
#include "Obj.h"
class CORaven :
    public CObj
{
public:
    CORaven();
    ~CORaven();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Player;

	CObj* pSellect_BackGroundEffect1;
	CObj* pSellect_BackGroundEffect2;
	CObj* pSellect_AlphaEffect;
	CObj* pSellect_AlphaInEffect;

	CObj* pSellect_Boss;

	bool deadswitch;
	bool Alphaswitch;
	bool SpawnSwitch = false;

	int MonsterCnt = 0;

	bool SW_AlphaIn = false;

	int DummyAlphaInCnt;
	int DummyAlphaOutCnt;
};

