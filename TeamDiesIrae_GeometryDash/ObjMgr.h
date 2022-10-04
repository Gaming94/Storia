#pragma once
class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();

public:
	void AddObject(CObj* pObj, ObjID::ID eID);
	void AddObject(CObj* pObj, ObjID::ID eID, float _x, float _y);

public:
	int Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public:
	static CObjMgr* GetInstance()
	{
		if (m_pInstacne == nullptr)
		{
			m_pInstacne = new CObjMgr;
		}
		return m_pInstacne;
	}

	void DestroyInstance()
	{
		if (m_pInstacne != nullptr)
		{
			delete m_pInstacne;
			m_pInstacne = nullptr;
		}
	}

public:
	static CObjMgr*		m_pInstacne;
	OBJLIST				m_Objlist[ObjID::OBJ_END];
};

