#pragma once
#include <time.h>

HWND hWnd1, hWnd2;
HINSTANCE hInst;

LRESULT CALLBACK WndProc3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc4(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildUpProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildDownProc(HWND, UINT, WPARAM, LPARAM);

int width = 100;
int chk = 0;

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc3;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)WHITE_BRUSH;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = NULL;

	wcex.lpfnWndProc = ChildUpProc;
	wcex.lpszClassName = L"ChildUp";
	RegisterClassEx(&wcex);
	wcex.lpfnWndProc = ChildDownProc;
	wcex.lpszClassName = L"ChildDown";
	RegisterClassEx(&wcex);

	return RegisterClassEx(&wcex);
}
void PopSubWindow(WNDCLASS wClass, HWND hWnd, LPARAM lParam) {
	TCHAR str[256];
	if (chk == 0)
	{
		wsprintf(str, TEXT("Packet No. %d, %s Protocol, Destination IP : %s"), lParam);
		wClass.cbClsExtra = 0;
		wClass.cbWndExtra = 0;
		wClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wClass.hInstance = hInst;
		wClass.lpfnWndProc = (WNDPROC)WndProc3;
		wClass.lpszClassName = str;
		wClass.lpszMenuName = NULL;
		wClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&wClass);

		hWnd = CreateWindow(str, str, WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE, 150, 300, 1000, 400, hWnd, 0, hInst, NULL);
		chk++;
	}
}

LRESULT CALLBACK WndProc3(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	static RECT rt;

	HDC hDC = GetDC(hWnd);

	TCHAR str[256];
	int i, j, tmp = 0, tmp2 = 0;

	switch (msg)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &rt);
		point.x = rt.left;
		point.y = rt.top;
		ScreenToClient(hWnd, &point);

		/*MyRegisterClass(hInst);
		hWnd1 = CreateWindow(L"ChildUp", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 1000, 300, hWnd, 0, hInst, NULL);
		hWnd2 = CreateWindow(L"ChildDown", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 300, 1000, 300, hWnd, 0, hInst, NULL);
		*/

		return 0;

	case WM_SIZE:
		/*if (wParam != SIZE_MINIMIZED) {
			MoveWindow(hWnd1, 0, 0, 1000, 300, TRUE);
			MoveWindow(hWnd2, 300, 0, rt.right, rt.bottom, TRUE);
		}*/
		return 0;

	case WM_PAINT:
		
		wsprintf(str, TEXT("destination ip : %d.%d.%d.%d"), 0, 0, 0, 0);
		TextOut(hDC, point.x, point.y, str, lstrlen(str));
		wsprintf(str, TEXT("hex view"));
		TextOut(hDC, point.x, point.y + 120, str, lstrlen(str));
			
		// (return된 Hex 값이라 가정하고) 랜덤 60개 16진수 출력
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 20; j++) {
				wsprintf(str, TEXT("%02X"), rand() % 256);
				TextOut(hDC, point.x + tmp, point.y + 150 + tmp2, str, lstrlen(str));
				tmp += 45;
			}
			tmp = 0;
			tmp2 += 15;
		}
		break;
		return 0;

	case WM_CLOSE:
		chk--;
		DestroyWindow(hWnd);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK ChildUpProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK ChildDownProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
