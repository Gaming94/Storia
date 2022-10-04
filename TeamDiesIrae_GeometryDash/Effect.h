#pragma once
class CEffect
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void Init() = 0;
	virtual void LateInit() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
};

