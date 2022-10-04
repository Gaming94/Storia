#pragma once
class CObj;

template <typename T>
class AbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Init();
	
		return pObj;
	}

	static CObj* CreateObj(int x, int y)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);
		pObj->LateInit();
		return pObj;
	}

	static CObj* CreateObj(int x, int y, bool _TF)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);
		pObj->CanMoveInit(_TF);
		pObj->LateInit();
		return pObj;
	}
};
