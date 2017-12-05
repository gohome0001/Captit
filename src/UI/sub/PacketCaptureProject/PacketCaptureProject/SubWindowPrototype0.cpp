#include <windows.h>
//#include <atltypes.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;
HWND sub;
int cnt = 0, id;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	char szAppName[] = "PacketCaptureProject";
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInst;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName;
	if (!RegisterClass(&WndClass)) return NULL;


	WndClass.lpfnWndProc = WndProc2;
	WndClass.lpszClassName = "sub";
	if (!RegisterClass(&WndClass)) return NULL;

	hWnd = CreateWindow(
		szAppName, szAppName,
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT,
		NULL, NULL, hInst, NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	CreateWindow(TEXT("button"), TEXT("PACKET ID 0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 1010, 25, hWnd, (HMENU)0, hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("PACKET ID 1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 25, 1010, 25, hWnd, (HMENU)1, hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("PACKET ID 2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 50, 1010, 25, hWnd, (HMENU)2, hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("PACKET ID 3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 75, 1010, 25, hWnd, (HMENU)3, hInst, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DWORD ws_num = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
	ws_num = ws_num & (~(WS_SYSMENU | WS_BORDER));
	HDC hdc;
	hdc = GetDC(hWnd);
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0: case 1: case 2: case 3:
			if (cnt == 0) {
				sub = CreateWindow("sub", "PacketDetails",
					ws_num | WS_CHILD | WS_VISIBLE | WS_CAPTION,
					0, 250, 1010, 240,
					hWnd, NULL, _hInstance, NULL);
				cnt++;
				id = LOWORD(wParam);
			}
			else return 0;
		}
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	CPoint point;
	static RECT rt;
	HDC hdc = GetDC(sub);
	TCHAR str[256];
	switch (msg)
	{
	case WM_CREATE:
		GetWindowRect(hWnd, &rt);
		point.x = rt.left;
		point.y = rt.top;
		ScreenToClient(hWnd, &point);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(str, TEXT("Packet Selected - No. %d"), id);
		TextOut(hdc, point.x, point.y, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
