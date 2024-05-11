#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

    srand((unsigned int)time(NULL));

    hWnd = CreateWindow(lpszClass, lpszWindowName,
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME,
        100, 50, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HDC hDC = GetDC(hWnd);

    int xCoords[10] = { 0 };
    int yCoords[10] = { 0 };

    for (int i = 0; i < 10; ++i) {
        int x, y;
        bool isDuplicate;
        do {
            isDuplicate = false;
            x = (rand() % 70 + 1) * 10;
            y = (rand() % 50 + 1) * 10;

            for (int j = 0; j < i; ++j) {
                if (abs(x - xCoords[j]) <= 10 && abs(y - yCoords[j]) <= 10) {
                    isDuplicate = true;
                    break;
                }
            }
        } while (isDuplicate);

        xCoords[i] = x;
        yCoords[i] = y;

        TCHAR str[100];
        _stprintf_s(str, 100, _T("%d: (%d, %d)"), i + 1, x, y);
        TextOut(hDC, x, y, str, _tcslen(str));
    }

    TCHAR centerStr[100];
    int centerX = 400;
    int centerY = 300;
    _stprintf_s(centerStr, 100, _T("0: (%d, %d)"), centerX, centerY);
    TextOut(hDC, centerX, centerY, centerStr, _tcslen(centerStr));

    ReleaseDC(hWnd, hDC);

    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
    switch (iMessage) {
    case WM_CREATE:
        break;

    case WM_PAINT:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, IParam);
}