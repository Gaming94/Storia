#pragma once
#include "Obj.h"
class COMonster_Practice :
	public CObj
{
public:
	COMonster_Practice();
	~COMonster_Practice();

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

	//�ִϸ��̼�
	TCHAR* m_pFrameKey;

	//���� �̺�Ʈ
	bool Deav_Event;

	//���� ����
	bool isMoving;
	bool isAttack;

	//���ݰ���
	CObj* pSellect_AttackRect;
};

