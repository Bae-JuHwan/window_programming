#include <Windows.h>
#include <tchar.h>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME,
		100, 50, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	int num;
	RECT rect;
	int x, y, n, m;
	TCHAR str[30] = { '0' };

	switch (iMessage) {
	case WM_CREATE:
		srand((unsigned)time(NULL));
		break;
	case WM_KEYUP:
		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		x = rand() % 501;
		y = rand() % 301;
		n = rand() % 19 + 1;
		m = rand() % 31;

		for (int i = 1; i <= m; ++i) {
			wsprintf(str, _T("%d, %d, %d, %d"), x, y, n, m);
			TextOut(hDC, 10, 10, str, lstrlen(str));
		}
		for (int i = 1; i <= m; ++i) {
			wsprintf(str, _T("%d * %d = %d"), n, i, n * i);
			TextOut(hDC, x, y + i * 20, str, lstrlen(str));
		}

		CreateCaret(hWnd, NULL, 2, 20);
		SetCaretPos(x, y);
		ShowCaret(hWnd);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, IParam);
}