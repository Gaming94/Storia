#pragma once
#include "Obj.h"
class COSkillBox :
	public CObj
{
public:
	COSkillBox();
	~COSkillBox();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:

};

