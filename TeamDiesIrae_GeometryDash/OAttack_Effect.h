#pragma once
#include "Obj.h"
class COAttack_Effect :
	public CObj
{
public:
	COAttack_Effect();
	virtual ~COAttack_Effect();

public:
	void SetFrame(TCHAR* _pFrame) { m_pFrameKey = _pFrame; }

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	DWORD	dwFrameTime;

	TCHAR*	m_pFrameKey;
	int		m_iDrawID;

	int		m_CharNum;
};

