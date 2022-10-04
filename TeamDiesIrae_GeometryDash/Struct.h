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
	int iFrameStart;	// 스프라이트의 x축 시작점
	int iFrameEnd;		// 스프라이트의 x축 끝점
	int iFrameScene;	// 스프라이트의 y축 시작점
	int iFrameSceneEnd;

	DWORD dwFrameTime;	// 
	DWORD dwFrameSpd;	// 재생 속도
}FRAME;

struct SBLENDFUNCTION
{
	BYTE	Blend0p;
	BYTE	BlendFlags;
	BYTE	SourceConstantAlpha;
	BYTE	AlphaFormat;
};