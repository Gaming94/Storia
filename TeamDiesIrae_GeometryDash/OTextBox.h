#pragma once
#include "Obj.h"
class COTextBox :
	public CObj
{
public:
	COTextBox();
	~COTextBox();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CObj* pSellect_Text;
	CObj* pSellect_Teller_Alponso;
	CObj* pSellect_Teller_Leo;

	BLENDFUNCTION blend;
};

