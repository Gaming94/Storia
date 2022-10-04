#pragma once
#include "Obj.h"
class COBckGroundEffect :
    public CObj
{
public:
	COBckGroundEffect();
	~COBckGroundEffect();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

