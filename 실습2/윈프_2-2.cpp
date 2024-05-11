#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows Program";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int n, m;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdParam, int nCmdShow)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    n = rand() % 9 + 2;
    m = rand() % 9 + 2;

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
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = lpszClass;
    WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszWindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hDC;
    RECT clientRect;
    int cellWidth, cellHeight;

    switch (iMessage) {
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &clientRect);

        cellWidth = clientRect.right / n;
        cellHeight = clientRect.bottom / m;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                COLORREF textColor = RGB(rand() % 256, rand() % 256, rand() % 256);
                COLORREF backColor = RGB(rand() % 256, rand() % 256, rand() % 256);
                HBRUSH hBrush = CreateSolidBrush(backColor);
                SelectObject(hDC, hBrush);

                int xPos = i * cellWidth;
                int yPos = j * cellHeight;
                RECT cellRect = { xPos, yPos, xPos + cellWidth, yPos + cellHeight };

                SetBkColor(hDC, textColor);
                DrawText(hDC, _T("abcdefg"), 7, &cellRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

                DeleteObject(hBrush);
            }
        }

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, iMessage, wParam, lParam);
    }
    return 0;
}