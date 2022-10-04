#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr* CObjMgr::m_pInstacne = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(CObj * pObj, ObjID::ID eID)
{
	// ������Ʈ ����Ʈ�� �߰��մϴ�
	m_Objlist[eID].push_back(pObj);
}

void CObjMgr::AddObject(CObj * pObj, ObjID::ID eID, float _x, float _y)
{
}

int CObjMgr::Update()
{
	for (int i = 0; i < ObjID::OBJ_END; ++i)
	{
		for (auto Iter = m_Objlist[i].begin(); Iter != m_Objlist[i].end();)
		{
			int Event = (*Iter)->Update();

			if (m_Objlist[i].empty())
			{
				return 1;
			}

			if (Event == DEAD_EVENT)
			{
				Iter = m_Objlist[i].erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}

	return 0;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < ObjID::OBJ_END; ++i)
	{
		for (auto& pObject : m_Objlist[i])
		{
			pObject->LateUpdate();
			if (m_Objlist[i].empty())
			{
				return;
			}
		}
	}
	// ������Ʈ�� �������� :: ĳ���� | ����������Ʈ
	CColigionMgr::CollisionRectBLend(m_Objlist[ObjID::OBJ_CHARACTER], m_Objlist[ObjID::OBJ_BLENDOBJ]);

	// ������Ʈ�� �������� :: ĳ���� | ����
	CColigionMgr::CollisionRectAttk(m_Objlist[ObjID::OBJ_CHARACTER], m_Objlist[ObjID::OBJ_MONSTER]);
}

void CObjMgr::Render(HDC hdc)
{
	for (int i = 0; i < ObjID::OBJ_END; ++i)
	{
		for (auto& pObject : m_Objlist[i])
		{
			pObject->Render(hdc);
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < ObjID::OBJ_END; ++i)
	{
		for_each(m_Objlist[i].begin(), m_Objlist[i].end(),
			[](auto& ptr)
		{
			if (ptr)
			{
				delete ptr;
				ptr = nullptr;
			}
		});
		m_Objlist[i].clear();
	}
}
