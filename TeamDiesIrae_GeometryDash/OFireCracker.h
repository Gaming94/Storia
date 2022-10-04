#pragma once
#include "Obj.h"
class COFireCracker :
	public CObj
{
public:
	COFireCracker();
	~COFireCracker();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

