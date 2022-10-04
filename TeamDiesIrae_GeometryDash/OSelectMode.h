#pragma once
#include "Obj.h"
class COSelectMode :
	public CObj
{
public:
	COSelectMode();
	~COSelectMode();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

