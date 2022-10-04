#pragma once
#include "Obj.h"
class COHit_Effect :
    public CObj
{
public:
	COHit_Effect();
	virtual ~COHit_Effect();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	DWORD	dwFrameTime;
};

