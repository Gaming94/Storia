#pragma once
#include "Obj.h"
class COHorseRace :
	public CObj
{
public:
	COHorseRace();
	~COHorseRace();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void ScrollFnc();
	void Restart();
private:
	CObj* pSellect_Player1;
	CObj* pSellect_Player2;
	CObj* pSellect_Player3;
	CObj* pSellect_FireCracker;
	CObj* pSellect_Numbering;

	int Goal;
	int RandSpeed;

	int Grade;
	int Rank[3];

	bool isStart = 0;
	bool isRacing[3] = { 0, };

	DWORD dwTime = GetTickCount64();
	DWORD dwOldTime = GetTickCount64();

	//scroll
	int Max_Size = 2223;
	int Scroll = 0;

	bool Scrolling = 0;
	bool StageClear = 1;

	//캐릭터 등장 전
	bool IsStageStart;
	bool isGoto;

	bool FireCracker = 0;
	bool FireCrackerSwitch = 0;
};

