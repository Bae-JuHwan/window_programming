#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>

#define IDC_EDIT_INPUT 1001
#define IDC_BUTTON_INPUT 1002

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"2-11";
LPCTSTR lpszWindowName = L"2-11";

struct ShapeInfo {
	int type;
	int x1, y1, x2, y2;
	int thickness;
	int size;
};

void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int thickness, COLORREF borderColor, COLORREF fillColor) {
	POINT points[3] = { {x1, y2}, {x2, y2}, {(x1 + x2) / 2, y1} };
	HPEN hBorderPen = CreatePen(PS_SOLID, thickness, borderColor);
	HBRUSH hFillBrush = CreateSolidBrush(fillColor);
	SelectObject(hdc, hBorderPen);
	SelectObject(hdc, hFillBrush);
	Polygon(hdc, points, 3);
	DeleteObject(hBorderPen);
	DeleteObject(hFillBrush);
}

void DrawRectangle(HDC hdc, int x1, int y1, int x2, int y2, int thickness, COLORREF borderColor, COLORREF fillColor) {
	HPEN hBorderPen = CreatePen(PS_SOLID, thickness, borderColor);
	HBRUSH hFillBrush = CreateSolidBrush(fillColor);
	SelectObject(hdc, hBorderPen);
	SelectObject(hdc, hFillBrush);
	Rectangle(hdc, x1, y1, x2, y2);
	DeleteObject(hBorderPen);
	DeleteObject(hFillBrush);
}

void DrawPentagon(HDC hdc, int x1, int y1, int x2, int y2, int thickness, COLORREF borderColor, COLORREF fillColor) {
	POINT points[5] = { {x1, (y1 + y2) / 2}, {(x1 + x2) * 1 / 3, y2}, {(x1 + x2) * 2 / 3, y2},{x2, (y1 + y2) / 2},{(x1 + x2) / 2, y1} };
	HPEN hBorderPen = CreatePen(PS_SOLID, thickness, borderColor);
	HBRUSH hFillBrush = CreateSolidBrush(fillColor);
	SelectObject(hdc, hBorderPen);
	SelectObject(hdc, hFillBrush);
	Polygon(hdc, points, 5);
	DeleteObject(hBorderPen);
	DeleteObject(hFillBrush);
}

void DrawCircle(HDC hdc, int x1, int y1, int x2, int y2, int thickness, COLORREF borderColor, COLORREF fillColor) {
	HPEN hBorderPen = CreatePen(PS_SOLID, thickness, borderColor);
	HBRUSH hFillBrush = CreateSolidBrush(fillColor);
	SelectObject(hdc, hBorderPen);
	SelectObject(hdc, hFillBrush);
	Ellipse(hdc, x1, y1, x2, y2);
	DeleteObject(hBorderPen);
	DeleteObject(hFillBrush);
}

vector<ShapeInfo> shapes;
const int MAX_SHAPES = 10;

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

	switch (iMessage) {
	case WM_CREATE:
		CreateWindow(TEXT("EDIT"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			300, 500, 200, 20,
			hWnd, (HMENU)IDC_EDIT_INPUT, g_hInst, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("Input"),
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			520, 500, 100, 20,
			hWnd, (HMENU)IDC_BUTTON_INPUT, g_hInst, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_INPUT:
		{
			TCHAR szBuffer[256];
			GetDlgItemText(hWnd, IDC_EDIT_INPUT, szBuffer, 256);
			for (int i = 0; szBuffer[i]; i++) {
				if (szBuffer[i] == ',')
					szBuffer[i] = ' ';
			}

			ShapeInfo shape;
			_stscanf_s(szBuffer, _T("%d %d %d %d %d %d"),
				&shape.type, &shape.x1, &shape.y1, &shape.x2, &shape.y2, &shape.thickness);

			shapes.push_back(shape);

			if (shapes.size() > MAX_SHAPES)
				shapes.erase(shapes.begin());

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ADD:
			for (size_t i = 0; i < shapes.size(); ++i) {
				if (shapes[i].thickness < 10) {
					shapes[i].thickness++;
				}
				else if(shapes[i].thickness > 10) {
					int dx = (shapes[i].x2 - shapes[i].x1) / 10;
					int dy = (shapes[i].y2 - shapes[i].y1) / 10;
					shapes[i].x1 -= dx;
					shapes[i].y1 -= dy;
					shapes[i].x2 += dx;
					shapes[i].y2 += dy;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_SUBTRACT:
			for (size_t i = 0; i < shapes.size(); ++i) {
				if (shapes[i].thickness > 1) {
					shapes[i].thickness--;
				}
				else if(shapes[i].thickness < 1) {
					int dx = (shapes[i].x2 - shapes[i].x1) / 10;
					int dy = (shapes[i].y2 - shapes[i].y1) / 10;
					shapes[i].x1 += dx;
					shapes[i].y1 += dy;
					shapes[i].x2 -= dx;
					shapes[i].y2 -= dy;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (size_t i = 0; i < shapes.size(); ++i) {
			switch (shapes[i].type) {
			case 1:
				SetPixel(hDC, shapes[i].x1, shapes[i].y1, RGB(255, 0, 0));
				break;
			case 2:
				MoveToEx(hDC, shapes[i].x1, shapes[i].y1, NULL);
				LineTo(hDC, shapes[i].x2, shapes[i].y2);
				break;
			case 3:
				DrawTriangle(hDC, shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].thickness, RGB(0, 0, 255), RGB(255, 0, 0));
				break;
			case 4:
				DrawRectangle(hDC, shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].thickness, RGB(0, 0, 255), RGB(255, 0, 0));
				break;
			case 5:
				DrawPentagon(hDC, shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].thickness, RGB(0, 0, 255), RGB(255, 0, 0));
				break;
			case 6:
				DrawCircle(hDC, shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].thickness, RGB(0, 0, 255), RGB(255, 0, 0));
				break;
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