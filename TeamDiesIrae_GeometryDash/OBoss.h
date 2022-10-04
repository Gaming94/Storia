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
    //�ִϸ��̼�
    TCHAR* m_pFrameKey;

    //���ݰ���
    CObj* pSellect_AttackRect;

    bool isStart;
};

