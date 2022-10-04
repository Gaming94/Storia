#pragma once
#include "Obj.h"
class COSelectCharacter :
	public CObj
{
public:
	COSelectCharacter();
	~COSelectCharacter();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	POINT pt;

	RECT AlponsoRect;
	RECT LeoRect;

	CObj* pSellect_Alponso;
	CObj* pSellect_Leo;

	CObj* pSellect_TextBox;

	CObj* pSellect_AlphaEffect;

	WCHAR StoryText1[100] = L"캐릭터 선택창 <임시 텍스트>";
	DWORD TextTime;

	int DummyAlphaCnt = 0;

	bool IsStart = 0;

	bool Zoom = false;
	int ZoomCnt = 0;
};

