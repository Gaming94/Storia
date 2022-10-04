#pragma once
#include "Scene.h"
class CSSanctuary :
	public CScene
{
public:
	CSSanctuary();
	~CSSanctuary();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Sanctuary;
};

