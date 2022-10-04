#pragma once
#include "Obj.h"
class COSelectMap :
	public CObj
{
public:
	COSelectMap();
	~COSelectMap();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	int m_RealSizeX = 2274;

	CObj* pSellect_AlphaEffect;

	CObj* pSellect_Alponso;
	CObj* pSellect_Leo;

	CObj* pSellect_Char;


	int m_SelectMapArrX[8];
	int m_SelectMapArrY[8];

	int m_ChoiceMap;

	int Effect = 300;
	//int Effect = 3;

private:
	bool SW_Alpha = false;

	bool SW_FadeOut = false;
	bool SW_FadeIn = false;

	float FadeOutCnt = 0.3;
	float FadeInCnt = 0;
};

namespace eSelectMap
{
	enum ID
	{
		MAP_ROCOTOWN = 0,
		MAP_VOLCANO,
		MAP_BEROIYA,
		MAP_SANCTUARY,
		MAP_OLDTREE,
		MAP_VALONBREY,
		MAP_RAVEN = 7,
		MAP_END
	};
};

