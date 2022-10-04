#pragma once
#include "Obj.h"
class COShadow :
    public CObj
{
public:
    COShadow();
    ~COShadow();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:

};

