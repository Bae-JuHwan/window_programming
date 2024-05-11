#include <Windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"¸Þ¸ðÀå";

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
    static SIZE size;
    static TCHAR str[10][31];
    static int count = 0;
    static int line = 0;
    static bool toggleUpperCase = false;
    
    switch (iMessage) {
    case WM_CREATE:
        CreateCaret(hWnd, NULL, 2, 20);
        ShowCaret(hWnd);
        break;
    case WM_KEYUP:
        if (wParam == VK_LEFT) {
            if (count > 0) {
                SetCaretPos(size.cx, size.cy);
            }
            else if (count == 0 && line > 0) {
                line--;
                count = lstrlen(str[line]);
                SetCaretPos(count * size.cx, line * size.cy);
            }
        }
        else if (wParam == VK_UP) {
            if (line > 0) {
                SetCaretPos(size.cx, size.cy);
            }
        }
        else if (wParam == VK_RIGHT) {
            if (count < 30) {
                SetCaretPos(size.cx, size.cy);
            }
            else if (count == 30 && line < 9) {
                line++;
                count = 0;
                SetCaretPos(count * size.cx, line * size.cy);
            }
        }
        else if (wParam == VK_DOWN) {
            if (line < 9) {
                SetCaretPos(size.cx, size.cy);
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_CHAR:
        if (wParam == VK_RETURN) {
            if (line < 9) {
                line++;
                count = 0;
                SetCaretPos(0, (line)*size.cy);
            }
            else if (line == 9) {
                line = 0;
                count = 0;
                SetCaretPos(0, 0);
            }
            break;
        }
        else if (wParam == VK_BACK) {
            if (count > 0) {
                count--;
                str[line][count] = '\0';

                if (count == 0 && line > 0) {
                    line--;
                    count = lstrlen(str[line]);
                }
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        else if (wParam == VK_ESCAPE) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 30; ++j) {
                    str[i][j] = '\0';
                    line = 0;
                    count = 0;
                    SetCaretPos(0, 0);
                }
            }
            break;
        }
        else if (wParam == VK_TAB) {
            int spaceToAdd = 5 - (count % 5);
            if (count + spaceToAdd <= 30) {
                for (int i = 0; i < spaceToAdd; ++i) {
                    for (int j = count; j >= count - i; --j) {
                        str[line][j + 1] = str[line][j];
                    }
                    str[line][count - i] = ' ';
                    count++;
                }
                SetCaretPos((count % 30) * size.cx, (line)*size.cy);
            }
            break;
        }
        else if (wParam == VK_F1) {
            toggleUpperCase = !toggleUpperCase;
        }
        else if (count < 30) {
            if (line < 10 && count < 30) {
                if (toggleUpperCase) {
                    str[line][count++] = toupper(wParam);
                }
                else {
                    str[line][count++] = wParam;
                }
                str[line][count] = '\0';
            }
        }
        else if (count >= 30) {
            if (line < 9) {
                line++;
                count = 0;
                SetCaretPos(0, (line)*size.cy);
            }
            else {
                line = 0;
                count = 0;
                SetCaretPos(0, 0);
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        for (int i = 0; i <= line; ++i) {
            GetTextExtentPoint32(hDC, str[i], lstrlen(str[i]), &size);
            TextOut(hDC, 0, i * size.cy, str[i], lstrlen(str[i]));
            SetCaretPos(size.cx, line * size.cy);
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, IParam);
}