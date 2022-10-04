#pragma once
#include "OLeo.h"

class CMain
{
public:
	CMain();
	~CMain();

public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HDC m_hdc;
	
};

