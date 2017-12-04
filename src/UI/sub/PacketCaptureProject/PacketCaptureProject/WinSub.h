#pragma once
#include <stdlib.h>
#include <time.h>

HWND hWnd1, hWnd2;
HINSTANCE hInst;

LRESULT CALLBACK WndProc3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc4(HWND, UINT, WPARAM, LPARAM);

int width = 100;
int chk = 0;

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

		return 0;

	case WM_PAINT:
		wsprintf(str, TEXT("destination ip : %d.%d.%d.%d"), 0, 0, 0, 0);
		TextOut(hDC, point.x, point.y, str, lstrlen(str));
		wsprintf(str, TEXT("hex view"));
		TextOut(hDC, point.x, point.y + 60, str, lstrlen(str));

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 20; j++) {
				wsprintf(str, TEXT("%02X"), rand() % 256);
				TextOut(hDC, point.x + tmp, point.y + 90 + tmp2, str, lstrlen(str));
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

LRESULT CALLBACK WndProc4(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	switch (msg)
	{
	case WM_CREATE:
	case WM_PAINT:
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
