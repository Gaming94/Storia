#include "stdafx.h"
#include "BG_Bitmap.h"


CBG_Bitmap::CBG_Bitmap()
{
	//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}


CBG_Bitmap::~CBG_Bitmap()
{
	Release();
}

void CBG_Bitmap::LoadBmp(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_bBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_bBitmap);
}

//void CBG_Bitmap::LoadPNG(const TCHAR * pFilePath)
//{
//	Image* image = NULL;
//	IStream* pStream = NULL;
//
//	HRSRC hResource = FindResource(nullptr, 0, pFilePath);
//	if (CreateStreamOnHGlobal(NULL, TRUE, &pStream) == S_OK)
//	{
//		PVOID pResourceData = LockResource(g_hInstance);
//		DWORD imageSize = SizeofResource(g_hInstance, hResource);
//		DWORD dwReadWrite = 0;
//
//		pStream->Write(pResourceData, imageSize, &dwReadWrite);
//		image = Image::FromStream(pStream);
//		pStream->Release();
//	}
//}

void CBG_Bitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_bBitmap);
	DeleteDC(m_hMemDC);
}

int CBG_Bitmap::LoadBmp_X(const TCHAR* pFilePath)
{
	BITMAP bit;

	m_bBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(m_bBitmap, sizeof(BITMAP), &bit);
	
	return bit.bmWidth;
}

int CBG_Bitmap::LoadBmp_Y(const TCHAR* pFilePath)
{
	BITMAP bit;

	m_bBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(m_bBitmap, sizeof(BITMAP), &bit);

	return bit.bmHeight;
}

//BITMAP CBG_Bitmap::GetBitmap()
//{
//	BITMAP bit;
//	GetObject(m_bBitmap, sizeof(BITMAP), &bit);
//	bit.bmWidth;
//	return BITMAP();
//}
