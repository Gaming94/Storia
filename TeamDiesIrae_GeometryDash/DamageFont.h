#pragma once
#include "Effect.h"
class CDamageFont :
    public CEffect
{
public:
    CDamageFont();
    ~CDamageFont();

public:
    virtual void Init() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

private:
    RECT m_tRect;
    INFO m_tInfo;

    CObj* pObj;
};

