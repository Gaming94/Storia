#pragma once
#include "Obj.h"
class COMarket :
    public CObj
{
public:
    COMarket();
    ~COMarket();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	wchar_t* wPotionCnt;
	wchar_t* wMoneyCnt;
	wchar_t* wPlayerAtk;
	wchar_t* wPlayerHP;
	wchar_t* wPlayerDef;

	WCHAR	WLPotionCnt[5];
	WCHAR	WLMoneyCnt[5];
	
	//stat
	WCHAR	WLPlayerAtk[5];
	WCHAR	WLPlayerHP[5];
	WCHAR	WLPlayerDef[5];

	WCHAR	WLWeaponStat[5];

	int PlayerAtk;
	int PlayerPotion;
	int PlayerMoney;
	int PlayerHp;
	int PlayerDef;

	int MoneyCnt = 3;
	int PotionCnt = 1;

	bool ItemOn = 0;
};

