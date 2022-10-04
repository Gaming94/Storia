#include "stdafx.h"
#include "COAttackRect.h"


COAttackRect::COAttackRect()
{
}


COAttackRect::~COAttackRect()
{
	Release();
}

void COAttackRect::Init()
{
	m_tInfo.FCX = 100;
	m_tInfo.FCY = 100;
}

void COAttackRect::LateInit()
{
}

int COAttackRect::Update()
{
	return 0;
}

void COAttackRect::LateUpdate()
{
}

void COAttackRect::Render(HDC hdc)
{
	if (CKeyMgr::GetInstance()->KeyPressing('R'))
	{
		CObj::UpdateRect();
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void COAttackRect::Release()
{
}
