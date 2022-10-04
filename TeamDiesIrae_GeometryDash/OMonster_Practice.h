#pragma once
#include "Obj.h"
class COMonster_Practice :
	public CObj
{
public:
	COMonster_Practice();
	~COMonster_Practice();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void Move_Left();
	void Move_Right();

	void SceneChange();

private:

	//움직일 거리
	int Purpose_DistX = 100;
	int Purpose_DistY = 100;
	
	//패턴
	int Move_Dist;
	int RandMove;
	bool MoveSwitch;

	//애니메이션
	TCHAR* m_pFrameKey;

	//다이 이벤트
	bool Deav_Event;

	//현재 상태
	bool isMoving;
	bool isAttack;

	//공격관련
	CObj* pSellect_AttackRect;
};

