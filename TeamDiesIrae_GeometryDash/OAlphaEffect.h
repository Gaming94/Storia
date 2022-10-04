#pragma once
#include "Obj.h"
class COAlphaEffect :
	public CObj
{
public:
	COAlphaEffect();
	~COAlphaEffect();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	BLENDFUNCTION blend;
	
	int blendCnt = 255;

	int RblendCnt = 0;
};

