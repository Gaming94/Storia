#pragma once
#include "Obj.h"
class COLeo :
	public CObj
{
public:
	COLeo();
	~COLeo();

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
	POINT		m_ChMove;

	float		m_pShSpeed;
	float		m_pPlusSpeed;

	bool		m_IsMoving;
	bool		m_IsAttacking;
	//bool		m_IsIdle;

	bool		Jump_State;
	int			JumpTime;
	int			JumpPower;
	int			JumpStartPosition;
	int			JumpDistance;
	float		Jump_height;


	//첫 시간
	DWORD		m_dwPreTick;
	//현재 시간
	DWORD		m_dwCurTick;

	TCHAR*		m_pFrameKey;
	bool		m_Character_IDLE;

	CObj*		pSellect_AttackRect;
	CObj*		pSellect_Shadow;
	bool		m_IsAttack = 0;

	float		m_JumpShadowX;
	float		m_JumpShadowY;
};

