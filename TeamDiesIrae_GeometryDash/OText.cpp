#include "stdafx.h"

#include "OText.h"


COText::COText()
	:m_TextOutCnt(0), PrintTextTF(0)
{
}


COText::~COText()
{
}

void COText::Init()
{
	TextTime = GetTickCount();
}

void COText::LateInit()
{
}

int COText::Update()
{
	if (m_bIsDead == true)
	{
		return DEAD_EVENT;
	}


	switch (ChapterNumber)
	{
	case 1:
		//튜토리얼
		wcscpy_s(StoryTeller[1], L"알폰소");
		wcscpy_s(StoryText[1], L"여기가 왕위쟁탈전을 벌인다는 곳이야??");

		wcscpy_s(StoryTeller[2], L"알폰소");
		wcscpy_s(StoryText[2], L"세상 어떤 왕국에 왕자들끼리 왕위를 두고 다투는게 전통인곳이 다 있담");

		wcscpy_s(StoryTeller[3], L"레오");
		wcscpy_s(StoryText[3], L"누구를 지지할지는 정했어?");

		wcscpy_s(StoryTeller[4], L"알폰소");
		wcscpy_s(StoryText[4], L"난 언제나 열세쪽으로 움직이잖아, 제일 약한곳이 할게 많아 재미있지 않겠어?");

		wcscpy_s(StoryTeller[5], L"레오");
		wcscpy_s(StoryText[5], L"또 이상한 병이 도졌군 가기전에 몸이나 움직여봐 새로운 몸이 잘 맞는지 확인해 봐야지");

		wcscpy_s(StoryTeller[6], L"레오");
		wcscpy_s(StoryText[6], L"몸에 무리 없으면 다시 말을 걸어줘");

		wcscpy_s(StoryTeller[7], L"알폰소");
		wcscpy_s(StoryText[7], L"몸을 다 풀면 다시 말을 걸어줘");

		wcscpy_s(StoryTeller[8], L"System");
		wcscpy_s(StoryText[8], L"방향키와 마우스를 이용해 캐릭터를 움직일 수 있습니다");

		wcscpy_s(StoryTeller[9], L"System");
		wcscpy_s(StoryText[9], L"Ctrl키를 눌러 공격을 할 수 있습니다");
		break;

	case 2:
		wcscpy_s(StoryTeller[0], L"레오");
		wcscpy_s(StoryText[0], L"몸은 어때?");

		wcscpy_s(StoryTeller[1], L"알폰소");
		wcscpy_s(StoryText[1], L"괜찮네 바로 움직여도 될 것 같아 왕자들 정보 정리된거 있어?");

		wcscpy_s(StoryTeller[2], L"알폰소");
		wcscpy_s(StoryText[2], L"측근이 한명도 없는 왕자라 딱 좋군 수고했어 바로 출발해보도록 할게");

		wcscpy_s(StoryTeller[2], L"레오");
		wcscpy_s(StoryText[2], L"이번 여행도 재밌게 즐기다 오길 바래");
		break;

	case 3:
		wcscpy_s(StoryTeller[0], L"레오");
		wcscpy_s(StoryText[0], L"몸은 어때?");

		break;
	}

	return 0;
}

void COText::LateUpdate()
{
	m_CurTextNumber = TextNumber;

	if (m_PreTextNumber != m_CurTextNumber)
	{
		TextOutCnt = 0;
	}
}

void COText::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	
	if (TextOnOff == true)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 350, 730, StoryTeller[TextNumber], wcslen(StoryTeller[TextNumber]));

		if (TextTime + 40 < GetTickCount64())
		{
			if (TextOutCnt < wcslen(StoryText[TextNumber]))
			{
				TextOutCnt++;
				TextTime = (DWORD)GetTickCount64();
			}
		}
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 330, 800, StoryText[TextNumber], TextOutCnt);
		m_PreTextNumber = m_CurTextNumber;
	}


}
	
void COText::Release()
{
}


//OPAQUE 불투명한 배경을 사용한다 배경색상에 의해 뒤쪽 그림이 지워진다
	//존나 신기해 
	//개신기해
	//존시나 신기해애애

	//strcpy -> wcspy
	//wcscpy_s(StoryText1, L"반가워요");

	//strlen-> wcslen


	//SetBkMode(hdc, TRANSPARENT);
	//SetTextColor(hdc, RGB(255, 255, 255));
	//
	//
	//if (TextTime + 40 < GetTickCount64())
	//{
	//	if (TextOutCnt < wcslen(StoryText1))
	//	{
	//		TextOutCnt++;
	//		TextTime = GetTickCount64();
	//	}
	//}
	//TextOut(hdc, 300, 450, StoryText1, TextOutCnt);

	//데미지 주는것도 계산 완료
	//int 애들 단위별로 깍아서 pKey값으로 숫자데미지 가져오기