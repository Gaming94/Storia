#include "stdafx.h"
#include "BG_Bitmap.h"
#include "BmpMgr.h"

CBMPMgr* CBMPMgr::m_pInstance = nullptr;

CBMPMgr::CBMPMgr()
{
}


CBMPMgr::~CBMPMgr()
{
	Release();
}

HDC CBMPMgr::FindBackGroundImage(const TCHAR * pImgKey)
{
	auto Iter_Bitmap = find_if(m_BackGroundBit.begin(), m_BackGroundBit.end(),
		[&pImgKey](auto& MyPair)
	{
		return !lstrcmp(pImgKey, MyPair.first);
	});

	if (m_BackGroundBit.end() == Iter_Bitmap)
		return nullptr;

	return Iter_Bitmap->second->GetMemDC();
}
 
HDC CBMPMgr::FindImg(const TCHAR * pFilePath)
{
	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&pFilePath](auto& Mypair)
	{
		return !lstrcmp(pFilePath, Mypair.first);
	});

	if (m_MapBit.end() == Iter_Find)
	{
		return nullptr;
	}

	return Iter_Find->second->GetMemDC();
}

//¿¬½À
//void CBMPMgr::InsertPng(const TCHAR * pFilePath, const TCHAR * pImgKey)
//{
//	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
//		[&pFilePath](auto& MyPair)
//	{
//		return !lstrcmp(pFilePath, MyPair.first);
//	});
//	if (m_MapBit.end() == Iter_Find)
//	{
//		CBG_Bitmap*pBmp = new CBG_Bitmap;
//		pBmp->LoadPNG(pFilePath);
//
//		m_MapBit.insert({ pImgKey, pBmp });
//	}
//}
//
//HDC CBMPMgr::FindPng(const TCHAR * pFilePath)
//{
//	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
//		[&pFilePath](auto& Mypair)
//	{
//		return !lstrcmp(pFilePath, Mypair.first);
//	});
//
//	if (m_MapBit.end() == Iter_Find)
//	{
//		return nullptr;
//	}
//
//	return Iter_Find->second->GetMemDC();
//}

int CBMPMgr::FindImg_SizeX(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&pFilePath](auto& Mypair)
	{
		return !lstrcmp(pFilePath, Mypair.first);
	});

	if (m_MapBit.end() == Iter_Find)
	{
		return 0;
	}

	return Iter_Find->second->LoadBmp_X(pImgKey);
}

int CBMPMgr::FindImg_SizeY(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&pFilePath](auto& Mypair)
	{
		return !lstrcmp(pFilePath, Mypair.first);
	});

	if (m_MapBit.end() == Iter_Find)
	{
		return 0;
	}

	return Iter_Find->second->LoadBmp_Y(pImgKey);
}

void CBMPMgr::InsertBackGroundBmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto iter_find = find_if(m_BackGroundBit.begin(), m_BackGroundBit.end(),
		[&pImgKey](auto& MyPair)
	{
		return !lstrcmp(pImgKey, MyPair.first);
	});

	if (m_BackGroundBit.end() == iter_find)
	{
		CBG_Bitmap*	pBmp = new CBG_Bitmap;
		pBmp->LoadBmp(pFilePath);

		m_BackGroundBit.insert({ pImgKey, pBmp });
	}
}

void CBMPMgr::InsertImg(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto Iter_Find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&pFilePath](auto& MyPair)
	{
		return !lstrcmp(pFilePath, MyPair.first);
	});
	if (m_MapBit.end() == Iter_Find)
	{
		CBG_Bitmap*pBmp = new CBG_Bitmap;
		pBmp->LoadBmp(pFilePath);

		m_MapBit.insert({ pImgKey, pBmp });
	}
}


void CBMPMgr::Release()
{
	for_each(m_BackGroundBit.begin(), m_BackGroundBit.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	for_each(m_MapBit.begin(), m_MapBit.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_BackGroundBit.clear();
	m_MapBit.clear();
}
