#pragma once
class CEffect;
class CEffectMgr
{
public:
	CEffectMgr();
	~CEffectMgr();

public:
	void SetWhatChar(int _CharNum);
	void SetPosition(int _Left, int _Top, int _Right, int _Bottom) { m_tRect.left = _Left, m_tRect.top = _Top, m_tRect.right = _Right, m_tRect.bottom = _Bottom; }
	void SetPosition(int _FX, int _FY)							{ m_tInfo.FX = _FX, m_tInfo.FY = _FY; }
	void SetBiggest(int _FCX, int _FCY)							{ m_tInfo.FCX = _FCX, m_tInfo.FCY = _FCY; }
	void SetObjectType(int _Type)								{ m_ObjectType = _Type; }

public:
	int GetPosition_Left()										{ return m_tRect.left; }
	int GetPosition_Right()										{ return m_tRect.right; }
	int GetPosition_Top()										{ return m_tRect.top; }
	int GetPosition_Bottom()									{ return m_tRect.bottom; }

	int GetPosition_FX()										{return m_tInfo.FX;}
	int GetPosition_FY()										{return m_tInfo.FY;}

	int GetSize_FCX()											{ return m_tInfo.FCX; }
	int GetSize_FCY()											{ return m_tInfo.FCY; }

	int GetWhatChar()											{ return m_CharNum; }
	int GetObjectType()											{ return m_ObjectType; }

public:
	enum EFFECTID
	{
		EFFECT_NULL,
		EFFECT_PLAYERATTACK,
		EFFECT_PLAYER_CSKILL,
		EFFECT_PLAYERDEATH,
		EFFECT_HIT,
		EFFECT_END
	};

public:
	void Init();
	int Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public:
	void Effect_Change(EFFECTID eID);

public:
	static CEffectMgr* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CEffectMgr;
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
	static CEffectMgr*		m_pInstance;

	CEffect*				m_pEffect;

	EFFECTID				m_eCurEffect;
	EFFECTID				m_ePreEffect;

	INFO					m_tInfo;
	RECT					m_tRect;

	int						m_CharNum;
	
	int						m_ObjectType;
};

