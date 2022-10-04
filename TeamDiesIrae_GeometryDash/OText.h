#pragma once
#include "Obj.h"
class COText :
	public CObj
{
public:
	COText();
	~COText();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	WCHAR StoryText[100][100];
	WCHAR StoryTeller[100][100];
	DWORD TextTime;
	
	int m_TextOutCnt;

	bool PrintTextTF;

	int m_CurTextNumber;
	int m_PreTextNumber;


};

