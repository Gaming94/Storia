#pragma once
#include "Scene.h"
class CSMiniGame :
	public CScene
{
public:
	CSMiniGame();
	~CSMiniGame();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	BLENDFUNCTION blend;
};

