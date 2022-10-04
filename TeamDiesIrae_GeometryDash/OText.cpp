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
		//Ʃ�丮��
		wcscpy_s(StoryTeller[1], L"������");
		wcscpy_s(StoryText[1], L"���Ⱑ ������Ż���� ���δٴ� ���̾�??");

		wcscpy_s(StoryTeller[2], L"������");
		wcscpy_s(StoryText[2], L"���� � �ձ��� ���ڵ鳢�� ������ �ΰ� �����°� �����ΰ��� �� �ִ�");

		wcscpy_s(StoryTeller[3], L"����");
		wcscpy_s(StoryText[3], L"������ ���������� ���߾�?");

		wcscpy_s(StoryTeller[4], L"������");
		wcscpy_s(StoryText[4], L"�� ������ ���������� �������ݾ�, ���� ���Ѱ��� �Ұ� ���� ������� �ʰھ�?");

		wcscpy_s(StoryTeller[5], L"����");
		wcscpy_s(StoryText[5], L"�� �̻��� ���� ������ �������� ���̳� �������� ���ο� ���� �� �´��� Ȯ���� ������");

		wcscpy_s(StoryTeller[6], L"����");
		wcscpy_s(StoryText[6], L"���� ���� ������ �ٽ� ���� �ɾ���");

		wcscpy_s(StoryTeller[7], L"������");
		wcscpy_s(StoryText[7], L"���� �� Ǯ�� �ٽ� ���� �ɾ���");

		wcscpy_s(StoryTeller[8], L"System");
		wcscpy_s(StoryText[8], L"����Ű�� ���콺�� �̿��� ĳ���͸� ������ �� �ֽ��ϴ�");

		wcscpy_s(StoryTeller[9], L"System");
		wcscpy_s(StoryText[9], L"CtrlŰ�� ���� ������ �� �� �ֽ��ϴ�");
		break;

	case 2:
		wcscpy_s(StoryTeller[0], L"����");
		wcscpy_s(StoryText[0], L"���� �?");

		wcscpy_s(StoryTeller[1], L"������");
		wcscpy_s(StoryText[1], L"������ �ٷ� �������� �� �� ���� ���ڵ� ���� �����Ȱ� �־�?");

		wcscpy_s(StoryTeller[2], L"������");
		wcscpy_s(StoryText[2], L"������ �Ѹ� ���� ���ڶ� �� ���� �����߾� �ٷ� ����غ����� �Ұ�");

		wcscpy_s(StoryTeller[2], L"����");
		wcscpy_s(StoryText[2], L"�̹� ���൵ ��հ� ���� ���� �ٷ�");
		break;

	case 3:
		wcscpy_s(StoryTeller[0], L"����");
		wcscpy_s(StoryText[0], L"���� �?");

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


//OPAQUE �������� ����� ����Ѵ� ������ ���� ���� �׸��� ��������
	//���� �ű��� 
	//���ű���
	//���ó� �ű��ؾ־�

	//strcpy -> wcspy
	//wcscpy_s(StoryText1, L"�ݰ�����");

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

	//������ �ִ°͵� ��� �Ϸ�
	//int �ֵ� �������� ��Ƽ� pKey������ ���ڵ����� ��������