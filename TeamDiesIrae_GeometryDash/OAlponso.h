#pragma once
#include "Obj.h"
class COAlponso :
	public CObj
{
public:
	COAlponso();
	~COAlponso();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void SceneChange();

public:
	void Jump();
	void Walk();

	float m_ToDestX;
	float m_ToDestY;

private:
	POINT m_ChMove;

	float m_pShSpeed;
	float m_pPlusSpeed;

	bool	Jump_State;
	bool	m_IsMoving;
	//bool	m_IsIdle;



	int JumpTime;
	int JumpPower;
	int JumpStartPosition;
	int JumpDistance;
	float Jump_height;


	//첫 시간
	DWORD		m_dwPreTick;
	//현재 시간
	DWORD		m_dwCurTick;

	TCHAR*		m_pFrameKey;
	bool		m_Character_IDLE;

	CObj* pSellect_Shadow;

	//BLENDFUNCTION m_Blend;
};

