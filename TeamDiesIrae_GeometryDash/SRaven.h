#pragma once
#include "Scene.h"
class CSRaven :
    public CScene
{
public:
	CSRaven();
	~CSRaven();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

