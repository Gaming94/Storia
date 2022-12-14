// TeamDiesIrae_GeometryDash.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TeamDiesIrae_GeometryDash.h"

#include "Main.h"

#define MAX_LOADSTRING 100

// 전역 변수:

HWND g_hWnd;
HINSTANCE g_hInstance;
int SelectCharacterNumber = 0;

int ClearMapPos = 0;
int BACKtoReturn = 0;
int Overlap_Hit = 1;

//BGM 스위치
int SelectCharBGMOnOff = false;
int SelectMapBGMOnOff = false;

int LodingShadow = false;
int SelectStageShadow = false;
//GdiplusStartupInput gpsi;


HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEAMDIESIRAEGEOMETRYDASH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEAMDIESIRAEGEOMETRYDASH));

    MSG msg;
	msg.message = WM_NULL;

	CMain Main;
	Main.Init();

	int FPS = 0;
	TCHAR szFPS[50] = L"";
	DWORD dwFPSTime = GetTickCount64();
	DWORD dwOldTime = GetTickCount64();

	//ULONG_PTR gpToken = 0;


	while (msg.message != WM_QUIT)
	{
		// 기본 메시지 루프입니다:
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (dwOldTime + 10 < GetTickCount64())
			{
				Main.Update();
				Main.LateUpdate();

				Main.Render();

				++FPS;
				dwOldTime = GetTickCount64();
			}
			if (dwFPSTime + 1000 < GetTickCount64())
			{
				swprintf_s(szFPS, L"<Team DiesIrae> FPS_Check : %d", FPS);
				FPS = 0;

				SetWindowText(g_hWnd, szFPS);
				dwFPSTime = GetTickCount64();
			}
		}
	}
	//GdiplusShutdown(gpToken);
    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEAMDIESIRAEGEOMETRYDASH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	  = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //int width = GetSystemMetrics(SM_CXSCREEN);
   //int height = GetSystemMetrics(SM_CYSCREEN);

   RECT rc = { 0,0,WINCX, WINCY };
   //RECT rc = { 0, 0, width, height};
   
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED,
	CW_USEDEFAULT, 0, rc.right - rc.left + 15, rc.bottom - rc.top + 35, nullptr, nullptr, hInstance, nullptr);

   //전체팝업으로 하고싶다면 WS_POPUP으로
	//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
	//CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top + 10, nullptr, nullptr, hInstance, nullptr);

	//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_EX_WINDOWEDGE,
	//CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top + 10, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;
   g_hInstance = hInstance;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case VK_ESCAPE:
			{
				DestroyWindow(hWnd);
			}
			break;
		}
	}
	break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
