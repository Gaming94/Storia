#pragma once
#include "Obj.h"
class COVolcano :
	public CObj
{
public:
	COVolcano();
	~COVolcano();

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
	CObj*		pSellect_AlphaEffect;

	bool IsSpawn;

	int Max_Size = 2223;
	int Scroll = 0;

	bool Scrolling = 0;
	bool StageClear = 1;

private:
	//캐릭터 등장 전
	bool IsStageStart;
	bool isGoto;

private:
	int MaxMonsterCnt;
	int MonsterCnt;

	int DummyAlphaCnt = 0;

	bool deadswitch;
	bool Alphaswitch = 0;
};

