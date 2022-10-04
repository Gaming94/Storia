#pragma once
#include "Obj.h"
class COCookie :
	public CObj
{
public:
	COCookie();
	~COCookie();

public:
	void SceneChange();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	TCHAR*		m_pFrameKey;

	CObj* pSellect_Shadow;
};

