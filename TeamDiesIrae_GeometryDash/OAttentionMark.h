#pragma once
#include "Obj.h"
class COAttentionMark :
	public CObj
{
public:
	COAttentionMark();
	~COAttentionMark();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	bool UpOrDown;

	float UpAndDown;
	int UpAndDownDest;
};

