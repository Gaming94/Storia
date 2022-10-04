#pragma once
#include "Obj.h"
class COAlponso_Illust :
	public CObj
{
public:
	COAlponso_Illust();
	~COAlponso_Illust();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

