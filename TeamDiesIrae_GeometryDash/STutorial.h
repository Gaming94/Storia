#pragma once
#include "Scene.h"
class COGround;

class CSTutorial :
	public CScene
{
public:
	CSTutorial();
	~CSTutorial();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Tutorial;
};

