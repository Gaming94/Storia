#pragma once
class CBG_Bitmap
{
public:
	CBG_Bitmap();
	~CBG_Bitmap();

public:
	HDC GetMemDC() { return m_hMemDC; }

public:
	void LoadBmp(const TCHAR* pFilePath);
	//void LoadPNG(const TCHAR* pFilePath);

	void Release();

	void DoubleBuffering(const TCHAR* _FirstObj, const TCHAR* _SecObj);

public:
	int LoadBmp_X(const TCHAR* pFilePath);
	int LoadBmp_Y(const TCHAR* pFilePath);
private:
	HDC			m_hMemDC;

	HBITMAP		m_bBitmap;
	HBITMAP		m_hOldBmp;

	//ULONG_PTR gdiplusToken;
	//GdiplusStartupInput gdiplusStartupInput;
	

	//알파블렌딩 연습
	//HBITMAP m_bitmap[3];
	//HBITMAP m_oldbitmap[3];
	//
	//BLENDFUNCTION m_BlendFunction;
	//int m_iAlpha;
};

