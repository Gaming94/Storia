#pragma once
class CBG_Bitmap;
class CBMPMgr
{
public:
	CBMPMgr();
	~CBMPMgr();

public:
	HDC FindBackGroundImage(const TCHAR* pImgKey);
	HDC FindImg(const TCHAR* pFilePath);
	
	//void InsertPng(const TCHAR * pFilePath, const TCHAR * pImgKey);
	//HDC	 FindPng(const TCHAR* pFilePath);
	
	int FindImg_SizeX(const TCHAR* pFilePath, const TCHAR* pImgKey);
	int FindImg_SizeY(const TCHAR* pFilePath, const TCHAR* pImgKey);

public:
	void InsertBackGroundBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void InsertImg(const TCHAR* pFilePath, const TCHAR* pImgKey);
	
	void Release();

public:
	static CBMPMgr* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBMPMgr;
		}
		return m_pInstance;
	}

	void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBMPMgr* m_pInstance;
	map<const TCHAR*, CBG_Bitmap*>	m_MapBit;
	map<const TCHAR*, CBG_Bitmap*>	m_BackGroundBit;

};

