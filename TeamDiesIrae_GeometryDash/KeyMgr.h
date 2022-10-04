#pragma once
class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool KeyPressing(int _Key);
	bool KeyDown(int _Key);
	bool KeyUp(int _Key);

public:
	bool AnyKeyDown();

public:
	void UpdateKey();

public:
	static CKeyMgr* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CKeyMgr;
		}
		return m_pInstance;
	}

	void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr*			m_pInstance;
	bool					m_KeyState[VK_MAX];

};

