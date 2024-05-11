#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void DrawTriangle(HDC hDC, int x, int y, int width, int height) {
	POINT points[3];

	points[0] = { x + width / 4, y + (3 * height / 4) };
	points[1] = { x + (width / 2), y + height / 4 };
	points[2] = { x + (3 * width / 4), y + (3 * height / 4) };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hDC, hBrush);
	Polygon(hDC, points, 3);
	DeleteObject(hBrush);
}

void DrawSandClock(HDC hDC, int x, int y, int width, int height) {
	POINT points[6];

	points[0] = { x + width / 4, y + height / 4 };
	points[1] = { x + (width / 2), y + height / 2 };
	points[2] = { x + (3*width / 4), y + height / 4 };

	points[3] = { x + width / 4, y + 3*(height / 4) };
	points[4] = { x + (3 * width / 4), y + (3*height / 4) };
	points[5] = { x + width / 2, y + height / 2 };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hDC, hBrush);
	Polygon(hDC, points, 3);
	Polygon(hDC, points + 3, 3);
	DeleteObject(hBrush);
}

void DrawPentagon(HDC hDC, int x, int y, int width, int height) {
	POINT points[5];

	points[0] = { x + width / 2, y + height / 6 };
	points[1] = { x + width / 6, y + height / 2 };
	points[2] = { x + width / 3, y + (5 * height / 6) };
	points[3] = { x + (2 * width / 3), y + (5 * height / 6) };
	points[4] = { x + (5 * width / 6), y + height / 2};

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hDC, hBrush);
	Polygon(hDC, points, 5);
	DeleteObject(hBrush);
}

BOOL DrawPie(HDC hDC, int xLeft, int yTop, int xRight, int yBottom, int xStart, int yStart, int xEnd, int yEnd) {
	POINT points[3];

	points[0] = { xStart, yStart };
	points[1] = { xEnd, yEnd };
	points[2] = { xRight, yBottom };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hDC, hBrush);
	BOOL result = Pie(hDC, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd);
	DeleteObject(hBrush);
	return result;
}

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"2-9";
LPCTSTR lpszWindowName = L"2-9";

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
		WS_OVERLAPPED | WS_SYSMENU,
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
	static RECT rc = { 0, 0, 800, 600 };
	BOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2);

	switch (iMessage) {
	case WM_CREATE:
		srand((unsigned)time(NULL));
		break;
	case WM_KEYUP:
		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == 't' || wParam == 'T') {
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			DrawTriangle(hDC, 200, 150, 550, 400);

			EndPaint(hWnd, &ps);
		}
		else if(wParam == 's' || wParam == 'S') {
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			DrawSandClock(hDC, 200, 150, 550, 400);

			EndPaint(hWnd, &ps);
		}
		else if(wParam == 'p' || wParam == 'P') {
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			DrawPentagon(hDC, 200, 150, 550, 400);

			EndPaint(hWnd, &ps);
		}
		else if(wParam == 'e' || wParam == 'E') {
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			DrawPie(hDC, 200, 150, 550, 400, 375, 150, 550, 275);

			EndPaint(hWnd, &ps);
		}
		else if (wParam == VK_LEFT) {

		}
		else if (wParam == VK_RIGHT) {

		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		Rectangle(hDC, 200,150, 550, 400);
		DrawTriangle(hDC, 50, 150, 150, 300);
		DrawSandClock(hDC, 200, 0, 400, 150);
		DrawPentagon(hDC, 500, 130, 330, 280);
		DrawPie(hDC, 250, 450, 500, 550, 375, 450, 500, 500);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, IParam);
}