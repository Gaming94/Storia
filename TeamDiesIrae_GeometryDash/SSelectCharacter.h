#pragma once
#include "Scene.h"
class CSSelectCharacter :
	public CScene
{
public:
	CSSelectCharacter();
	~CSSelectCharacter();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_SelectCharacter;
};