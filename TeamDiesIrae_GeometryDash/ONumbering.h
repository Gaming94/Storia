#pragma once
#include "Obj.h"
class CONumbering :
	public CObj
{
public:
	CONumbering();
	~CONumbering();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	int Number = 3;
};

