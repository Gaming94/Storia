#pragma once
#include "Scene.h"
class CSBeroia :
	public CScene
{
public:
	CSBeroia();
	~CSBeroia();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Beroia;
};

