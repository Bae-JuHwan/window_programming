#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>

typedef struct {
	int left;
	int top;
} GridCell;

void DrawTwoTriangle(HDC hdc, int x, int y, int width, int height) {
	POINT points[6];

	points[0] = { x + width / 4, y + (3 * height / 4) };
	points[1] = { x + (width / 2), y + height / 2 };
	points[2] = { x + (3 * width / 4), y + (3 * height / 4) };

	points[3] = { x + width / 4, y + height / 2 };
	points[4] = { x + (width / 2), y + height / 4 };
	points[5] = { x + (3 * width / 4), y + height / 2 };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 3);
	Polygon(hdc, points + 3, 3);
	DeleteObject(hBrush);
}

void DrawX(HDC hdc, int x, int y, int width, int height) {
	POINT points[4];

	points[0] = { x + width / 4, y + height / 4 };
	points[1] = { x + (3 * width / 4), y + (3 * height / 4) };

	points[2] = { x + (3 * width / 4), y + height / 4 };
	points[3] = { x + width / 4, y + (3 * height / 4) };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 2);
	Polygon(hdc, points + 2, 2);
	DeleteObject(hBrush);
}

void DrawF(HDC hdc, int x, int y, int width, int height) {
	POINT points[10];

	points[0] = { x + width / 4, y + height / 4 };
	points[1] = { x + (3 * width / 4), y + height / 4 };

	points[2] = { x + (3 * width / 4), y + height / 4 };
	points[3] = { x + (3 * width / 4), y + height / 2 };

	points[4] = { x + (3 * width / 4), y + height / 2 };
	points[5] = { x + width / 4, y + height / 2 };

	points[6] = { x + width / 4, y + height / 2 };
	points[7] = { x + width / 4, y + (3 * height / 4) };

	points[8] = { x + width / 4, y + (3 * height / 4) };
	points[9] = { x + (3 * width / 4), y + (3 * height / 4) };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 2);
	Polygon(hdc, points + 2, 2);
	Polygon(hdc, points + 4, 2);
	Polygon(hdc, points + 6, 2);
	Polygon(hdc, points + 8, 2);
	DeleteObject(hBrush);
}

void DrawButterFly(HDC hdc, int x, int y, int width, int height) {
	POINT points[6];

	points[0] = { x + width / 4, y + height / 4 };
	points[1] = { x + (width / 2), y + height / 2 };
	points[2] = { x + width / 4, y + (3 * height / 4) };

	points[3] = { x + width / 2, y + height / 2 };
	points[4] = { x + (3 * width / 4), y + height / 4 };
	points[5] = { x + (3 * width / 4), y + (3 * height / 4) };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 3);
	Polygon(hdc, points + 3, 3);
	DeleteObject(hBrush);
}

void DrawThreeRectangle(HDC hdc, int x, int y, int width, int height) {
	POINT points[12];

	points[0] = { x + width / 7, y + height / 4 };
	points[1] = { x + width / 7, y + (3 * height / 4) };
	points[2] = { x + (2 * width / 7), y + (3 * height / 4) };
	points[3] = { x + (2 * width / 7), y + height / 4 };

	points[4] = { x + (3 * width / 7), y + height / 4 };
	points[5] = { x + (3 * width / 7), y + (3 * height / 4) };
	points[6] = { x + (4 * width / 7), y + (3 * height / 4) };
	points[7] = { x + (4 * width / 7), y + height / 4 };

	points[8] = { x + (5 * width / 7), y + height / 4 };
	points[9] = { x + (5 * width / 7), y + (3 * height / 4) };
	points[10] = { x + (6 * width / 7), y + (3 * height / 4) };
	points[11] = { x + (6 * width / 7), y + height / 4 };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 4);
	Polygon(hdc, points + 4, 4);
	Polygon(hdc, points + 8, 4);
	DeleteObject(hBrush);
}

void DrawDiamond(HDC hdc, int x, int y, int width, int height) {
	POINT points[4];

	points[0] = { x + width / 2, y + height / 4 };
	points[1] = { x + (width / 4), y + height / 2 };
	points[2] = { x + width / 2, y + (3 * height / 4) };
	points[3] = { x + (3 * width / 4), y + height / 2 };

	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 4);
	DeleteObject(hBrush);
}

void DrawRandomShape(HDC hdc, int x, int y, int width, int height) {
	int shape = rand() % 6;

	COLORREF bkColor = RGB(rand() % 255, rand() % 255, rand() % 255);

	SetBkColor(hdc, bkColor);

	RECT rect = { x, y, x + width, y + height };
	HBRUSH hBrush = CreateSolidBrush(bkColor);
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);

	if (shape == 0) {
		DrawTwoTriangle(hdc, x, y, width, height);
	}
	else if(shape == 1){
		DrawX(hdc, x, y, width, height);
	}
	else if (shape == 2) {
		DrawF(hdc, x, y, width, height);
	}
	else if (shape == 3) {
		DrawButterFly(hdc, x, y, width, height);
	}
	else if (shape == 4) {
		DrawThreeRectangle(hdc, x, y, width, height);
	}
	else if (shape == 5) {
		DrawDiamond(hdc, x, y, width, height);
	}
}

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2-6";

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
	static GridCell gridCells[120];
	static int numGridCells = 0;
	
	PAINTSTRUCT ps;
	HDC hDC;
	static RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	static int width = rc.right - rc.left;
	static int height = rc.bottom - rc.top;
	int row, col;
	int lineSpacingX, lineSpacingY;

	switch (iMessage) {
	case WM_CREATE:
		srand((unsigned)time(NULL));
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		row = rand() % 9 + 2;
		lineSpacingX = width / row;
		col = rand() % 9 + 2;
		lineSpacingY = height / col;

		for (int i = 1; i < row; ++i) {
			MoveToEx(hDC, lineSpacingX * i, 0, NULL);
			LineTo(hDC, lineSpacingX * i, height);
		}
		
		for (int j = 1; j < col; ++j) {
			MoveToEx(hDC, 0, lineSpacingY * j, NULL);
			LineTo(hDC, width, lineSpacingY * j);
		}

		numGridCells = 0;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				gridCells[numGridCells].left = lineSpacingX * i;
				gridCells[numGridCells].top = lineSpacingY * j;

				DrawRandomShape(hDC, gridCells[numGridCells].left, gridCells[numGridCells].top, lineSpacingX, lineSpacingY);
				
				numGridCells++;
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, IParam);
}