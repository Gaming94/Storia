#pragma once
#include "Scene.h"
class CSLoading :
	public CScene
{
public:
	CSLoading();
	~CSLoading();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Loading;
};

