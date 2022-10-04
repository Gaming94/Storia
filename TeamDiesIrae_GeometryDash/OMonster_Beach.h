#pragma once
#include "Obj.h"
class COMonster_Beach :
    public CObj
{
public:
    COMonster_Beach();
    ~COMonster_Beach();
    
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

	//다이 이벤트
	bool Deav_Event;

	//애니메이션
	TCHAR* m_pFrameKey;

	//공격박스
	CObj* pSellect_AttackRect;

	//현재 상태
	bool isMoving;
	bool isAttack;
};

