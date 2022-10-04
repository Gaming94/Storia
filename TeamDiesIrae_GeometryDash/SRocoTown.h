#pragma once
#include "Scene.h"
class CSRocoTown :
	public CScene
{
public:
	CSRocoTown();
	~CSRocoTown();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

