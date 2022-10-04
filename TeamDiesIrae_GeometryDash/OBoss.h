#pragma once
#include "Obj.h"
class COBoss :
    public CObj
{
public:
    COBoss();
    ~COBoss();

public:
    virtual void Init();
    virtual int Update();
    virtual void LateUpdate();
    virtual void Render(HDC hdc);
    virtual void Release();

public:
    void SceneChange();

private:
    //애니메이션
    TCHAR* m_pFrameKey;

    //공격관련
    CObj* pSellect_AttackRect;

    bool isStart;
};

