#pragma once
#include "Obj.h"
class COAttackRect :
	public CObj
{
public:
	COAttackRect();
	~COAttackRect();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

