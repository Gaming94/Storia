#pragma once
class CColigionMgr
{
public:
	CColigionMgr();
	~CColigionMgr();

public:
	static void CollisionRectPO(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionRectAttk(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionRectCSkill(OBJLIST& dstLst, OBJLIST& srcLst);
	
	static void CollisionRectBLend(OBJLIST& dstLst, OBJLIST& srcLst);

public:
	static void CollisionRectTalk(OBJLIST& dstLst, OBJLIST& srcLst);

public:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);


};

