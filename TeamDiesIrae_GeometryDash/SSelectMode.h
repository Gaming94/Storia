#pragma once
#include "Scene.h"
class CSSelectMode :
	public CScene
{
public:
	CSSelectMode();
	~CSSelectMode();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

