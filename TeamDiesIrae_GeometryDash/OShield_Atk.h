#pragma once
#include "Obj.h"
class COShield_Atk :
    public CObj
{
public:
    COShield_Atk();
    ~COShield_Atk();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	float Dest_Dist;
	float Move_Dist;
};

