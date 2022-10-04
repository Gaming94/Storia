#pragma once

typedef struct SObjectInfo
{
	float FX;
	float FY;
	float FCX;
	float FCY;
}INFO;

typedef struct SObjectStatus
{
	int Cur_HP;
	int MAX_HP;
	int Atk;
	int Def;

	int Potion;
	int Money;

	int Weapon;
}STATUS;

struct SCatepaultInfo
{
	int HP;
};

typedef struct tagFrame
{
	int iFrameStart;	// ��������Ʈ�� x�� ������
	int iFrameEnd;		// ��������Ʈ�� x�� ����
	int iFrameScene;	// ��������Ʈ�� y�� ������
	int iFrameSceneEnd;

	DWORD dwFrameTime;	// 
	DWORD dwFrameSpd;	// ��� �ӵ�
}FRAME;

struct SBLENDFUNCTION
{
	BYTE	Blend0p;
	BYTE	BlendFlags;
	BYTE	SourceConstantAlpha;
	BYTE	AlphaFormat;
};