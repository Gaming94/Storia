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
	//캐릭터 오브젝트 충돌 사망
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
				//플레이어
				//평타
				if (((pDst->GetChar_CurStance() == Char_StanceID::ATTACK_R) && (pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
					|| ((pDst->GetChar_CurStance() == Char_StanceID::ATTACK_L) && pDst->GetChar_CurFrame() == 7) && (pDst->GetChar_CurSceneN() == 0))
				{
					CEffectMgr::GetInstance()->SetPosition(pSrc->GetRect().left, pSrc->GetRect().top, pSrc->GetRect().right, pSrc->GetRect().bottom);
					CEffectMgr::GetInstance()->Effect_Change(CEffectMgr::EFFECTID::EFFECT_HIT);

					pSrc->SetDamage(pDst->GetStatus().Atk);
				}

				//Z 스킬일때
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


				// 몬스터 일반공격
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
	// 캐릭터 오브젝트와 블렌딩 오브젝트와 겹쳤다면
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			// 블렌드 효과를 조절하여  블렌딩 오브젝트의 알파값을 조절하여 투명처리한다
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
	//두 사각형의 가로, 세로 측 반지름 합을 각각 구한다.
	float fSumRadX = (pSrc->GetInfo().FCX + ((pDst->GetTriangleObstacleInfo().right) - (pDst->GetTriangleObstacleInfo().left))*0.5);
	float fSumRadY = (pSrc->GetInfo().FCY + ((pDst->GetTriangleObstacleInfo().bottom) - (pDst->GetTriangleObstacleInfo().top))*0.5);
	
	//두 사각형의 x, y축 중점 간의 거리를 구한다.
	//fabs(x) : x에 대한 절대값을 구해주는 함수 <cmath>
	
	float fDistX = fabs(pDst->GetRect().right) - (pSrc->GetInfo().FX);
	float fDistY = fabs(pDst->GetRect().bottom) - (pSrc->GetInfo().FY);
	
	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		//파고든 거리를 구한다
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;
		return true;
	}
	
	//원본 (TBO_SemiFinal과 살짝 변동 부분이 있으니 참조바람
	return false;
}
