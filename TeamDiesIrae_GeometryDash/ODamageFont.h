#pragma once
#include "Obj.h"
class CODamageFont :
    public CObj
{
public:
    CODamageFont();
    ~CODamageFont();

public:
    virtual void Init() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

private:
    int Damage;

    int PurPoseDst;
    int MoveDst;
};

