#include<windows.h>
#include<commctrl.h>
#include"UserDefine.h"
#include"resource.h"
#include<stdio.h>

#define MAX_FILENAME_SIZE 100
#define MAX_OPTION_X 600
#define MAX_OPTION_Y 400

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM , LPARAM);

static HWND hList, hList2,b1,b2,b3,b4 = NULL;

MSG msg;

HINSTANCE g_hInst;
HINSTANCE hInst;

WNDCLASS WndClass2;

HWND hpop;

LVCOLUMN COL;
LVITEM Li;

char* get_data(void)
{
	return "hello";
}

void MakeProcListView(HWND hWnd) {
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
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd,hWndListView;
	WNDCLASS WndClass;
	MSG Message;
	g_hInst = hInstance;
	LPCWSTR dd = L"Captit";
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
		TranslateMessage(&Message);				
		DispatchMessage(&Message);
	}
	return 0;
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	HFONT hFont,oldFont;
	static HWND btn1;
	switch (iMessage)
	{
	case WM_CREATE:
		btn1 = CreateWindow(L"button", L"jjhjhjhj", WS_CHILD | WS_VISIBLE |
			BS_3STATE, 200, 150, 160, 40, hWnd, (HMENU)IDC_BTN1, g_hInst, NULL);
		return 0;
	case WM_PAINT:
		hDC = GetDC(hWnd);
		hFont = CreateFont(22, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, NULL);
		oldFont = (HFONT)SelectObject(hDC, hFont);

		TextOut(hDC, 10, 13, L"Network Interface", lstrlen(L"Network Interface"));
		TextOut(hDC, (MAX_OPTION_X / 3)+15, 13, L"Premiscuous Mode", lstrlen(L"Premiscuous Mode"));
		TextOut(hDC, 2 * (MAX_OPTION_X / 3) + 13, 15, L"Monitor Mode", lstrlen(L"Monitor Mode"));

		MoveToEx(hDC, 7, 45, NULL);
		LineTo(hDC, MAX_OPTION_X-22, 45);

		MoveToEx(hDC, MAX_OPTION_X/3, 10,NULL);
		LineTo(hDC, MAX_OPTION_X / 3, 40);
		
		MoveToEx(hDC, 2 * (MAX_OPTION_X / 3), 10, NULL);
		LineTo(hDC, 2 * (MAX_OPTION_X / 3), 40);
		
		MoveToEx(hDC, 7, 105, NULL);
		LineTo(hDC, MAX_OPTION_X - 22, 105);

		MoveToEx(hDC, 7, 165, NULL);
		LineTo(hDC, MAX_OPTION_X - 22, 165);
		
		MoveToEx(hDC, 7, 225, NULL);
		LineTo(hDC, MAX_OPTION_X - 22, 225);

		TextOut(hDC, 65, 65, L"Wi-Fi", lstrlen(L"Wi-Fi"));
		TextOut(hDC, 75, 125, L"VPN", lstrlen(L"VPN"));
		TextOut(hDC, 55, 185, L"VMWARE", lstrlen(L"VMWARE"));

		
		SelectObject(hDC, oldFont);
		DeleteObject(hFont);
		return 0;

	}
	
	return DefWindowProc(hWnd, iMessage, wParam, lParam);

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	
	OPENFILENAME Ofn,Sav;
	TCHAR sFilePathName[MAX_FILENAME_SIZE];
	boolean flag=false;
	char* nam;
	static TCHAR sfilter[] = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	static TCHAR sfilter2[] = L"pcap(*.pcap)\0";
	LPWSTR ptr;
	static int lastIndex=0;
	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_FILE_SAVE://OPEN
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
		case ID_FILE_OPEN:
			//file save;
			memset(&Sav, 0, sizeof(OPENFILENAME));
			memset(&sFilePathName, 0, sizeof(MAX_FILENAME_SIZE));
			Sav.lStructSize = sizeof(OPENFILENAME);
			Sav.hwndOwner = hWnd;
			Sav.lpstrFilter = sfilter2;
			Sav.lpstrFile = sFilePathName;
			Sav.nMaxFile = MAX_FILENAME_SIZE;
			Sav.lpstrInitialDir = L"C:\\";
			if (GetSaveFileName(&Sav) != 0)
			{
				wsprintf(sFilePathName, L"%s 파일 선택", Ofn.lpstrFile);
				MessageBox(hWnd, sFilePathName, L"저장 선택", MB_OKCANCEL);
			}
			else
			{
				MessageBox(hWnd, L"저장을 취소하였습니다.", L"저장 취소", MB_OKCANCEL);
			}
			return 0;
		case ID_INFO:
			ShellExecute(NULL, L"open", L"chrome", L"www.github.com/gohome0001/Captit/blob/master/%EC%9A%94%EA%B5%AC%EC%82%AC%ED%95%AD.md", NULL, SW_SHOW);
			return 0;
		case ID_CAPTURE_START://capture start
			for (int i = 0;i<50;i++)
			{ 				
				nam = get_data();//data read
				if (flag)
					break;
				wchar_t wtext[20];
				mbstowcs(wtext, nam, strlen(nam) + 1);//char to lpwstr
				ptr = wtext;
				Li.iItem = i;
				ListView_InsertItem(hList, &Li);
				ListView_SetItemText(hList, i, 0, ptr);
				ListView_SetItemText(hList, i, 1, ptr);
			}
			return 0;
		case ID_CAPTURE_RESTART:
			ListView_DeleteAllItems(hList);
			SendMessage(hWnd, WM_COMMAND, ID_CAPTURE_START, lParam);
			return 0;
		case ID_CAPTURE_STOP:
			flag = true;
			return 0;
		case ID_OPTION:
			LPCWSTR dd2 = L"Option";
			WndClass2.cbClsExtra = 0;
			WndClass2.cbWndExtra = 0;
			WndClass2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			WndClass2.hCursor = LoadCursor(NULL, IDC_ARROW);
			WndClass2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			WndClass2.hInstance = hInst;
			WndClass2.lpfnWndProc = (WNDPROC)WndProc2;
			WndClass2.lpszClassName = dd2;
			WndClass2.lpszMenuName = NULL;
			WndClass2.style = CS_HREDRAW | CS_VREDRAW;
			RegisterClass(&WndClass2);
			hpop = CreateWindow(dd2, dd2, WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE, 500, 200, MAX_OPTION_X, MAX_OPTION_Y, hWnd, 0, hInst, NULL);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		}

		return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
