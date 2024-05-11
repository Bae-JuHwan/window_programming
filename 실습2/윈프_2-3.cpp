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
	int x, y, n, count;
	TCHAR str[20] = { 0 };

	switch (iMessage) {
	case WM_CREATE:
		srand((unsigned)time(NULL));
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
			InvalidateRect(hWnd, NULL, TRUE);
	case WM_KEYUP:
		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		x = rand() % 601;
		y = rand() % 401;
		n = rand() % 10;
		count = rand() % 16 + 5;

		for (int i = 0; i < count; i++)
			str[i] = ((int)n) + 48;

		SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
		
		for ( int i = 0; i < count; i++)
			TextOut(hDC, x, y+i*20, str, lstrlen(str));

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, IParam);
}