#pragma once
#include "Obj.h"
class COGround;
class COTutorial :
	public CObj
{
public:
	COTutorial();
	virtual ~COTutorial();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	//���� �Լ�

private:
	CObj*		pSellect_Player;
	CObj*		pSellect_NPC;

	CObj*		pSellect_Text;

	CObj*		pSellect_SkillBox;
	CObj*		pSellect_TextBox;
	CObj*		pSellect_AttentionMark;

	CObj*		pSellect_BlendObj1;
	CObj*		pSellect_BlendObj2;

	RECT		NPCRect;
	POINT		pt;

	//�ӽ�
	int			WhoIsTeller = 0;
	int			m_TextNumber;

	bool		StoryStart;
	bool		StoryComplete;
	bool		MoveComplete;
};

