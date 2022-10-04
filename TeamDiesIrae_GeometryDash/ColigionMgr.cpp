#include "stdafx.h"
#include "Obj.h"

#include "ColigionMgr.h"


CColigionMgr::CColigionMgr()
{
}


CColigionMgr::~CColigionMgr()
{
}


void CColigionMgr::CollisionRectPO(OBJLIST & dstLst, OBJLIST & srcLst)
{
	//ĳ���� ������Ʈ �浹 ���
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			if (IntersectRect(&rc, &pDst->GetRect(), &pSrc->GetRect()))
			{
				pSrc->SetDead();
			}
		}
	}
}

void CColigionMgr::CollisionRectAttk(OBJLIST & dstLst, OBJLIST & srcLst)
{
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			if (IntersectRect(&rc, &pDst->GetRect(), &pSrc->GetRect()))
			{
				//�÷��̾�
				//��Ÿ
				if (((pDst->GetChar_CurStance() == Char_StanceID::ATTACK_R) && (pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
					|| ((pDst->GetChar_CurStance() == Char_StanceID::ATTACK_L) && pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
				{
					CEffectMgr::GetInstance()->SetPosition(pSrc->GetRect().left, pSrc->GetRect().top, pSrc->GetRect().right, pSrc->GetRect().bottom);
					CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_HIT);

					pSrc->SetDamage(pDst->GetStatus().Atk);
				}

				//Z ��ų�϶�
				if (((pDst->GetChar_CurStance() == Char_StanceID::SKILL_R) && (pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
					|| ((pDst->GetChar_CurStance() == Char_StanceID::SKILL_R) && pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
				{
					if (CKeyMgr::GetInstance()->KeyPressing('Z'))
					{
						pSrc->SetDamage(pDst->GetStatus().Atk * 2);
					}

					if (CKeyMgr::GetInstance()->KeyPressing('C'))
					{
						pSrc->SetDamage(5);

						pSrc->HitBySkillCOnOff();

					}
				}


				// ���� �Ϲݰ���
				if (((pSrc->GetChar_CurStance() == Char_StanceID::ATTACK_R) && (pSrc->GetChar_CurFrame() == 4) && (pSrc->GetChar_CurSceneN() == 1))
					|| ((pSrc->GetChar_CurStance() == Char_StanceID::ATTACK_L) && pSrc->GetChar_CurFrame() == 4) && (pSrc->GetChar_CurSceneN() == 1))
				{
					pDst->SetDamage(pSrc->GetStatus().Atk);
				}
			}
			if (Overlap_Hit == true)
			{

			}
			else
			{
				break;
			}
		}
		//break;
	}
}

void CColigionMgr::CollisionRectCSkill(OBJLIST& dstLst, OBJLIST& srcLst)
{
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			if (IntersectRect(&rc, &pDst->GetRect(), &pSrc->GetRect()))
			{
				pSrc->SetPos(pSrc->GetInfo().FX, pSrc->GetInfo().FY - 10);
			}
		}
	}
}

void CColigionMgr::CollisionRectBLend(OBJLIST & dstLst, OBJLIST & srcLst)
{
	// ĳ���� ������Ʈ�� ���� ������Ʈ�� ���ƴٸ�
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			// ���� ȿ���� �����Ͽ�  ���� ������Ʈ�� ���İ��� �����Ͽ� ����ó���Ѵ�
			if (IntersectRect(&rc, &pDst->GetRect(), &pSrc->GetRect()))
			{
				pSrc->SetBlendOnOff(true);
			}
			else
				pSrc->SetBlendOnOff(false);
		}
	}
}

void CColigionMgr::CollisionRectTalk(OBJLIST & dstLst, OBJLIST & srcLst)
{
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			if (IntersectRect(&rc, &pDst->GetRect(), &pSrc->GetRect()))
			{
			}
		}
	}

}

bool CColigionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	//�� �簢���� ����, ���� �� ������ ���� ���� ���Ѵ�.
	float fSumRadX = (pSrc->GetInfo().FCX + ((pDst->GetTriangleObstacleInfo().right) - (pDst->GetTriangleObstacleInfo().left))*0.5);
	float fSumRadY = (pSrc->GetInfo().FCY + ((pDst->GetTriangleObstacleInfo().bottom) - (pDst->GetTriangleObstacleInfo().top))*0.5);
	
	//�� �簢���� x, y�� ���� ���� �Ÿ��� ���Ѵ�.
	//fabs(x) : x�� ���� ���밪�� �����ִ� �Լ� <cmath>
	
	float fDistX = fabs(pDst->GetRect().right) - (pSrc->GetInfo().FX);
	float fDistY = fabs(pDst->GetRect().bottom) - (pSrc->GetInfo().FY);
	
	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		//�İ�� �Ÿ��� ���Ѵ�
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;
		return true;
	}
	
	//���� (TBO_SemiFinal�� ��¦ ���� �κ��� ������ �����ٶ�
	return false;
}
