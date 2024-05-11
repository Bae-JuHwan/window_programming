#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"3-2";
LPCTSTR lpszWindowName = L"3-2";

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

    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        250, 0, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

struct CIRCLE {
    int nCenterX;
    int nCenterY;
    int radius;
    COLORREF color;
};
CIRCLE circle = { 450, 20, 20, RGB(0,0,255) };

struct RECTANGLE {
    RECT rectRegion;
    COLORREF color;
    int status = 0;         // 0이면 사각형이고, 1이면 사각형 없어짐.
};
RECTANGLE rectangle[24] = {};

void InitializeRectangles() {
    for (int i = 0; i < 24; ++i) {
        int row = i / 8;
        int col = i % 8;
        rectangle[i].rectRegion.left = 100 + (col * 100);
        rectangle[i].rectRegion.top = 600 + (row * 40);
        rectangle[i].rectRegion.right = 200 + (col * 100);
        rectangle[i].rectRegion.bottom = 640 + (row * 40);
        rectangle[i].color = RGB(255, 255, 0);
        rectangle[i].status = 0;
    }
}

void DrawCircle(HDC mdc) {
    HBRUSH hBrush = CreateSolidBrush(circle.color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
    Ellipse(mdc, circle.nCenterX - circle.radius, circle.nCenterY - circle.radius,
        circle.nCenterX + circle.radius, circle.nCenterY + circle.radius);
    SelectObject(mdc, oldBrush);
    DeleteObject(hBrush);
}

void DrawRectangles(HDC mdc) {
    for (int i = 0; i < 24; ++i) {
        RECTANGLE& rect = rectangle[i];
        if (rect.status == 0) {
            HBRUSH hBrush = CreateSolidBrush(rect.color);
            SelectObject(mdc, hBrush);
            Rectangle(mdc, rect.rectRegion.left, rect.rectRegion.top,
                rect.rectRegion.right, rect.rectRegion.bottom);
            DeleteObject(hBrush);
        }
    }
}

bool CheckCollision(const CIRCLE& circle, const RECTANGLE& rect) {
    int circleX = circle.nCenterX;
    int circleY = circle.nCenterY;

    int rectLeft = rect.rectRegion.left;
    int rectRight = rect.rectRegion.right;
    int rectTop = rect.rectRegion.top;
    int rectBottom = rect.rectRegion.bottom;

    if (circleX >= rectLeft - circle.radius && circleX <= rectRight + circle.radius && circleY >= rectTop - circle.radius && circleY <= rectBottom + circle.radius) {
        return true;
    }
}

void BounceCircle(RECTANGLE* rectangle, int rectCount, CIRCLE& circle, HWND hWnd) {
    int circleX = circle.nCenterX;
    int circleY = circle.nCenterY;
    int collisionIndex = -1;

    for (int i = 0; i < rectCount; ++i) {
        RECTANGLE& rect = rectangle[i];
        int rectLeft = rect.rectRegion.left;
        int rectRight = rect.rectRegion.right;
        int rectTop = rect.rectRegion.top;
        int rectBottom = rect.rectRegion.bottom;

        bool isclash = (circleX + circle.radius >= rectLeft && circleX - circle.radius <= rectRight &&
            circleY + circle.radius >= rectTop && circleY - circle.radius <= rectBottom);

        if (isclash) {
            rect.status = 1;
            collisionIndex = i;
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 2, 10, NULL);
            break;
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
    PAINTSTRUCT ps;
    HDC hDC, mDC;
    HBITMAP hBitmap;
    static RECT rect;
    static int Timer1Count = 0, Timer2Count = 0, Timer3Count = 0;
    COLORREF color;
    HBRUSH hBrush, oldBrush;

    switch (iMessage) {
    case WM_CREATE:
        //처음에 도형들의 크기나 위치를 정해주는곳
        InitializeRectangles();
        break;
    case WM_PAINT:
        GetClientRect(hWnd, &rect);
        hDC = BeginPaint(hWnd, &ps);
        mDC = CreateCompatibleDC(hDC);
        hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
        SelectObject(mDC, (HBITMAP)hBitmap);
        Rectangle(mDC, 0, 0, rect.right, rect.bottom);

        hBrush = CreateSolidBrush(circle.color);
        oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

        SelectObject(mDC, oldBrush);
        DeleteObject(hBrush);

        DrawCircle(mDC);
        DrawRectangles(mDC);

        BitBlt(hDC, 0, 0, rect.right, rect.bottom, mDC, 0, 0, SRCCOPY);

        DeleteDC(mDC);
        DeleteObject(hBitmap);
        EndPaint(hWnd, &ps);
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case 's':
        case 'S':
            SetTimer(hWnd, 1, 10, NULL);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        break;
    case WM_RBUTTONDOWN:
        break;
    case WM_TIMER:
        switch (wParam) {
        case 1:
            circle.nCenterY += 3;
            InvalidateRect(hWnd, NULL, false);
            BounceCircle(rectangle, 24, circle, hWnd);
            break;
        case 2:
            circle.nCenterX -= 3;
            circle.nCenterY -= 3;
            InvalidateRect(hWnd, NULL, false);
            break;
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, IParam);
}