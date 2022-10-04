#pragma once
#include "Obj.h"
class COLeo_Illust :
	public CObj
{
public:
	COLeo_Illust();
	~COLeo_Illust();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
};

