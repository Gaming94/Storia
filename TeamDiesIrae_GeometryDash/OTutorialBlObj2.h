#pragma once
#include "Obj.h"
class COTutorialBlObj2 :
	public CObj
{
public:
	COTutorialBlObj2();
	~COTutorialBlObj2();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	BLENDFUNCTION blend;
};

