// Win_Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win_Client.h"

// >> :
#include <list>
#include <vector>
#include <string>
using namespace std;

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#define WM_ASYNC WM_USER+1
// <<

// >> :
WSADATA		wsadata;
SOCKET		s;
SOCKADDR_IN	addr = { 0 };
TCHAR		msg[1000], str[1000], name[100];
char		buffer[1000];
int			msgLen;
int			nameLen;

int InitClient(HWND hWnd);
void CloseClient();

void SendMessageToServer();
void printChat();
void pushChat(TCHAR* strData);
void getEditText();

#define IDC_CHAT	100
#define IDC_EDIT	101
#define IDC_SEND	102
HWND		hEdit;
HWND		hChat;
HWND		hSend;
RECT		rect;

list<wstring> chatList;

BOOL CALLBACK    DlgProc_NameDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// << :

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WINCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINCLIENT));

    MSG msg;
	
    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINCLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINCLIENT);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &rect);
		hChat = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_READONLY
			| ES_AUTOVSCROLL | ES_MULTILINE, (rect.right / 6.0), 10, (rect.right / 3.0) * 2, (rect.bottom / 3.0) * 2 - 10,
			hWnd, (HMENU)IDC_CHAT, hInst, NULL);
		hEdit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER
			| ES_AUTOVSCROLL | ES_MULTILINE, (rect.right / 6.0), (rect.bottom / 3.0) * 2 + 10, (rect.right / 3.0) * 2, (rect.bottom / 3) - 20,
			hWnd, (HMENU)IDC_EDIT, hInst, NULL);
		hSend = CreateWindow(L"button", L"전송", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			(rect.right / 6.0) * 5 + 10, (rect.bottom / 3.0) * 2 + 10, 100, 50,
			hWnd, (HMENU)IDC_SEND, hInst, NULL);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_NAME_DIALOG), hWnd, DlgProc_NameDlg);
		return InitClient(hWnd);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDC_SEND:
				getEditText();
				SendMessageToServer();
				SetWindowText(hEdit, L"");
				printChat();
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		MoveWindow(hChat, (rect.right / 6.0), 10, (rect.right / 3.0) * 2, (rect.bottom / 3.0) * 2 - 10, TRUE);
		MoveWindow(hEdit, (rect.right / 6.0), (rect.bottom / 3.0) * 2 + 10, (rect.right / 3.0) * 2, (rect.bottom / 3) - 20, TRUE);
		MoveWindow(hSend, (rect.right / 6.0) * 5 + 10, (rect.bottom / 3.0) * 2 + 10, 100, 50, TRUE);
		return 0;
	case WM_ASYNC:
		{
			switch (lParam)
			{
			case FD_READ:
				msgLen = recv(s, buffer, 1000, 0);
				buffer[msgLen] = NULL;
#ifdef _UNICODE
				msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
				MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
				msg[msgLen] = NULL;
#else
				strcpy(msg, buffer);
#endif
				pushChat(msg);
				printChat();
			}
		}
		break;
	case WM_CHAR:
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		CloseClient();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int InitClient(HWND hWnd)
{
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);		// 정수값으로 유저구분 가능
	if (s == INVALID_SOCKET)
	{
		chatList.push_back(L"System\t: socket failed");
		printChat();
		return 0;
	}
	else
	{
		chatList.push_back(L"System\t: socket success");
		printChat();
	}

	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.219.180");
	if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		chatList.push_back(L"System\t: connect failed");
		printChat();
		return 0;
	}
	else
	{
		chatList.push_back(L"System\t: connect success");
		printChat();
	}
	WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
	return 1;
}

void CloseClient()
{
	closesocket(s);
	WSACleanup();
}

void SendMessageToServer()
{
	send(s, (LPSTR)buffer, msgLen + 1, 0);
}

void printChat()
{
	wstring strFullChat{};
	list<wstring>::iterator iterList{};

	iterList = chatList.begin();

	while (iterList != chatList.end())
	{
		strFullChat += (*iterList);
		strFullChat.push_back(L'\r');
		strFullChat.push_back(L'\n');
		iterList++;
	}

	SetWindowText(hChat, strFullChat.c_str());
}

void pushChat(TCHAR* strData)
{
	if (chatList.size() >= 50)
	{
		chatList.pop_front();
	}
	chatList.push_back(strData);
}

void getEditText()
{
	if (s == INVALID_SOCKET) return;
	msgLen = GetWindowTextLength(hEdit) + 1;
	GetWindowText(hEdit, str, msgLen);
	
	TCHAR str2[1000];
	lstrcpy(str2, name);
	lstrcat(str2, str);
	lstrcpy(str, str2);
	msgLen = _tcslen(str);
#ifdef _UNICODE
	msgLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msgLen, NULL, NULL);
#else
	strcpy(buffer, str);
	msgLen = strlen(buffer);
#endif
}

BOOL CALLBACK DlgProc_NameDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDD_NAME_OK)
		{
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 100);
			if (_tcscmp(name, L""))
			{
				lstrcat(name, L"\t: ");
				nameLen = _tcslen(name);
				EndDialog(hDlg, LOWORD(wParam));
			}
			else
			{
				MessageBox(hDlg, L"닉네임을 입력해주세요.", L"닉네임 입력 오류", MB_OK);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}