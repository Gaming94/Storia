#pragma once
#include "Obj.h"

class COAlponso;
class CORocoTown :
	public CObj
{
public:
	CORocoTown();
	~CORocoTown();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj*		pSellect_Player;
	//CObj*		pSellect_Monster;


	bool IsSpawn;

	int Max_Size = 2223;
	int Scroll = 0;

	bool Scrolling = 0;
	bool StageClear;

	COAlponso*	pMonsterPractice;
	map<int, CObj*>	m_MonsterMap;
	map<int, CObj*>::iterator Iter;
	int MonsterCnt = 0;

	bool LeoSkillONOFF = 0;

	bool	Jump_State;
	int JumpTime;
	int JumpPower;
	int JumpStartPosition;
	int JumpDistance;
	float Jump_height;

	int pup = 0;	
};

