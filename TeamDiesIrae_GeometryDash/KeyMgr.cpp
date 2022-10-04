#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_KeyState, sizeof(m_KeyState));
}


CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::KeyPressing(int _Key)
{
	if (GetAsyncKeyState(_Key) & 0x8000)
	{
		return true;
	}
	return false;
}

bool CKeyMgr::KeyDown(int _Key)
{
	if (!m_KeyState[_Key] && GetAsyncKeyState(_Key) & 0x8000)
	{
		m_KeyState[_Key] = !m_KeyState[_Key];
		return true;
	}
	return false;
}

bool CKeyMgr::KeyUp(int _Key)
{
	if (!m_KeyState[_Key] && GetAsyncKeyState(_Key) & 0x8000)
	{
		m_KeyState[_Key] = m_KeyState[_Key];
		return true;
	}
	return false;
}

bool CKeyMgr::AnyKeyDown()
{
	for (int i = 0; i < 255; i++)
	{
		if (i != 21)
		{
			if (m_KeyState[i] == true)
			{
				return true;
			}
		}
	}
	return false;
}

void CKeyMgr::UpdateKey()
{
	for (int i = 0; i < VK_MAX; i++)
	{
		if (m_KeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
		{
			m_KeyState[i] = !m_KeyState[i];
		}
		if (!m_KeyState[i] && GetAsyncKeyState(i) & 0x8000)
		{
			m_KeyState[i] = !m_KeyState[i];
		}
	}
}
