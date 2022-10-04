#pragma once
#include "Obj.h"
class COMonster_Beach :
    public CObj
{
public:
    COMonster_Beach();
    ~COMonster_Beach();
    
public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void Move_Left();
	void Move_Right();

	void SceneChange();

private:
	//������ �Ÿ�
	int Purpose_DistX = 100;
	int Purpose_DistY = 100;

	//����
	int Move_Dist;
	int RandMove;
	bool MoveSwitch;

	//���� �̺�Ʈ
	bool Deav_Event;

	//�ִϸ��̼�
	TCHAR* m_pFrameKey;

	//���ݹڽ�
	CObj* pSellect_AttackRect;

	//���� ����
	bool isMoving;
	bool isAttack;
};

