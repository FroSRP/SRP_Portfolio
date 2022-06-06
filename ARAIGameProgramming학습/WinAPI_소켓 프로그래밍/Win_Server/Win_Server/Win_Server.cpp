// Win_Server.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win_Server.h"

// >> :
#include <list>
#include <vector>
using namespace std;

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC WM_USER+1
// <<

// >> :
WSADATA		wsaData;
SOCKET		s, cs;
TCHAR		msg[1000];
SOCKADDR_IN	addr = { 0 }, c_addr;
int size, msgLen;
char buffer[1000];

int Init_Server(HWND hWnd);
int Close_Server();
list<SOCKET> socketList;

SOCKET AcceptSocket(HWND hWnd, SOCKET s, SOCKADDR_IN& c_addr);
void SendMessageToClient(char* buffer);
void ReadMessage(TCHAR* msg, char* buffer);
void CloseClient(SOCKET socket);

#define IDC_CHAT	100
HWND		hChat;
RECT		rect;
list<wstring> chatList;

void printChat();
void pushChat(TCHAR* strData);
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
    LoadStringW(hInstance, IDC_WINSERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINSERVER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINSERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINSERVER);
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
			| ES_AUTOVSCROLL | ES_MULTILINE, (rect.right / 6.0), 10, (rect.right / 3.0) * 2, rect.bottom - 10,
			hWnd, (HMENU)IDC_CHAT, hInst, NULL);
		return Init_Server(hWnd);
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			cs = AcceptSocket(hWnd, s, c_addr);
			break;
		case FD_READ:
			ReadMessage(msg, buffer);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case FD_CLOSE:
			CloseClient(s);
			break;
		}
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		MoveWindow(hChat, (rect.right / 6.0), 10, (rect.right / 3.0) * 2, rect.bottom - 10, TRUE);
		return 0;
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		Close_Server();
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

int Init_Server(HWND hWnd)
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
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

	if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		chatList.push_back(L"System\t: binding failed");
		printChat();
	}
	else
	{
		chatList.push_back(L"System\t: binding success");
		printChat();
	}

	WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);

	if (listen(s, 5) == -1)
	{
		chatList.push_back(L"System\t: listen failed");
		printChat();
		return 0;
	}
	else
	{
		chatList.push_back(L"System\t: listen success");
		printChat();
	}

	return 1;
}

int Close_Server()
{
	closesocket(s);
	WSACleanup();
	return 1;
}

SOCKET AcceptSocket(HWND hWnd, SOCKET s, SOCKADDR_IN & c_addr)
{
	SOCKET cs;
	int size;
	size = sizeof(c_addr);
	cs = accept(s, (LPSOCKADDR)&c_addr, &size);
	WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

	socketList.push_back(cs);

	return cs;
}

void SendMessageToClient(char * buffer)
{
	for (list<SOCKET>::iterator it = socketList.begin();
		it != socketList.end(); it++)
	{
		SOCKET cs = (*it);
		send(cs, (LPSTR)buffer, strlen(buffer) + 1, 0);
	}
}

void ReadMessage(TCHAR * msg, char * buffer)
{
	for (list<SOCKET>::iterator it = socketList.begin();
		it != socketList.end(); it++)
	{
		SOCKET cs = (*it);
		int msgLen = recv(cs, buffer, 100, 0);
		if (msgLen > 0)
		{
			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			msg[msgLen] = NULL;
#else
			strcpy(msg, buffer);
#endif _UNICODE
			pushChat(msg);
			printChat();

			SendMessageToClient(buffer);
		}
	}
}

void CloseClient(SOCKET socket)
{
	for (list<SOCKET>::iterator it = socketList.begin();
		it != socketList.end(); it++)
	{
		SOCKET cs = (*it);
		if (cs == socket)
		{
			closesocket(cs);
			it = socketList.erase(it);
			break;
		}
	}
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