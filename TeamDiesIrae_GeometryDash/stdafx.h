// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define _CRT_SECURE_NO_WARNINGS
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <io.h>

using namespace std;

//Gdi+
//#ifndef  ULONG_PTR
//#define ULONG_PTR unsigned long
//#endif // ! ULONG_PTR
//
//#include <Ole2.h>
//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment (lib, "Gdiplus.lib")

////멀티미디어 재생에 필요한 헤더와 라이브러리
#include<Vfw.h>
#pragma comment (lib, "vfw32.lib")
//
////FMOD 헤더(bgm)
#include"fmod.h"
#pragma comment (lib, "fmodex_vc.lib")

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.

// 98_Header
#include "Extern.h"
#include "Define.h"
#include "TypeDef.h"
#include "Enum.h"
#include "Struct.h"

// 97_DesignPattern
#include "SafeDeleteh.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "ColigionMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "EffectMgr.h"
#include "KeyMgr.h"


