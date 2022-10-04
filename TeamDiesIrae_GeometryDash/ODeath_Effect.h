#pragma once
#include "Obj.h"
class CODeath_Effect :
    public CObj
{
public:
	CODeath_Effect();
	virtual ~CODeath_Effect();

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

