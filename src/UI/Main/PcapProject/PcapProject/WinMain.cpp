#include<windows.h>
#include<commctrl.h>
#include"UserDefine.h"
#include"resource.h"
#define MAX_FILENAME_SIZE 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
static HWND hList = NULL;
MSG msg;
HINSTANCE g_hInst;
void MakeProcListView(HWND hWnd) {
	LVCOLUMN COL;
	LVITEM Li;

	hList = CreateWindow(WC_LISTVIEW,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_HSCROLL,
		10, 10, D_WINDOW_WIDTH - 35, D_WINDOW_HEIGHT - 100,hWnd,(HMENU)IDC_LIST,g_hInst,NULL);

	ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = L"NUM";
	COL.iSubItem = 0;
	ListView_InsertColumn(hList, 0, &COL);

	COL.cx = 100;
	COL.pszText = L"TIME";
	COL.iSubItem = 1;
	ListView_InsertColumn(hList, 1, &COL);

	COL.cx = 150;
	COL.pszText = L"SRC";
	COL.iSubItem = 2;
	ListView_InsertColumn(hList, 2, &COL);

	COL.cx = 150;
	COL.pszText = L"DEST";
	COL.iSubItem = 3;
	ListView_InsertColumn(hList, 3, &COL);

	COL.cx = 100;
	COL.pszText = L"PROTOCOL";
	COL.iSubItem = 4;
	ListView_InsertColumn(hList, 4, &COL);


	COL.cx = 50;
	COL.pszText = L"LEN";
	COL.iSubItem = 5;
	ListView_InsertColumn(hList, 5, &COL);

	COL.cx = 300;
	COL.pszText = L"DATA";
	COL.iSubItem = 6;
	ListView_InsertColumn(hList, 6, &COL);
	//세팅
	Li.mask = LVIF_TEXT;
	Li.state = 0;
	Li.stateMask = 0;
	Li.iSubItem = 0;
	Li.pszText = 0;

	for (int i = 0; i < 60; i++)
	{
		Li.iItem = i;
		ListView_InsertItem(hList, &Li);
		ListView_SetItemText(hList, i, 0, (LPWSTR)L"1");
		ListView_SetItemText(hList, i, 1, (LPWSTR)L"testa");
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HINSTANCE hInst;
	HWND hWnd,hWndListView;
	WNDCLASS WndClass;
	MSG Message;
	LPCWSTR dd = L"Practice";
	hInst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInst;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = dd;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);


	hWnd = CreateWindow(dd, dd, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, D_WINDOW_POSX, D_WINDOW_POSY, D_WINDOW_WIDTH, D_WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	MakeProcListView(hWnd);
	ShowWindow(hWnd, nCmdShow);
	
	
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);				//!< 키보드나 모든 이벤트를 받아옵니다.
		DispatchMessage(&Message);				//!< 이벤트를 WndProc으로 전달시키는 역할을 합니다.
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	
	OPENFILENAME Ofn;
	TCHAR sFilePathName[MAX_FILENAME_SIZE];
	
	static TCHAR sfilter[] = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	
	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_FILE_SAVE:
			memset(&Ofn, 0, sizeof(OPENFILENAME));
			memset(&sFilePathName, 0, sizeof(MAX_FILENAME_SIZE));
			Ofn.lStructSize = sizeof(OPENFILENAME);
			Ofn.hwndOwner = hWnd;
			Ofn.lpstrFilter = sfilter;
			Ofn.lpstrFile = sFilePathName;
			Ofn.nMaxFile = MAX_FILENAME_SIZE;
			Ofn.lpstrInitialDir = L"C:\\";
			if (GetOpenFileName(&Ofn) != 0)
			{
				wsprintf(sFilePathName, L"%s 파일 선택", Ofn.lpstrFile);
				MessageBox(hWnd, sFilePathName, L"불러오기 선택", MB_OKCANCEL);
			}
			else
			{
				MessageBox(hWnd, L"불러오기를 취소하였습니다.", L"불러오기 취소", MB_OKCANCEL);
			}
			return 0;
		case ID_INFO:
			ShellExecute(NULL, L"open", L"chrome", L"www.github.com/gohome0001/Captit/blob/master/%EC%9A%94%EA%B5%AC%EC%82%AC%ED%95%AD.md", NULL, SW_SHOW);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		}

		return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
