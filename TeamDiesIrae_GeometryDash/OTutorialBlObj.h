#pragma once
#include "Obj.h"
class COTutorialBlObj :
	public CObj
{
public:
	COTutorialBlObj();
	~COTutorialBlObj();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	BLENDFUNCTION blend;

	int Cnt = 0;
};

