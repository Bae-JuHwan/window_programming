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
    static SIZE size;
    static TCHAR str[10][31];
    static int currentLine = 0;
    static int currentPos = 0;

    switch (iMessage) {
    case WM_CREATE:
        CreateCaret(hWnd, NULL, 2, 20);
        ShowCaret(hWnd);
        break;
    case WM_CHAR:
        if (wParam == VK_RETURN) {
            if (currentLine < 9) {
                currentLine++;
                currentPos = 0;
                SetCaretPos(0, (currentLine)*size.cy);
            }
            else if(currentLine == 9) {
                currentLine = 0;
                currentPos = 0;
                SetCaretPos(0, 0);
            }
            //InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        else if (wParam == VK_BACK) {
            if (currentPos > 0) {
                currentPos--;
                str[currentLine][currentPos] = '\0';

                if (currentPos == 0 && currentLine > 0) {
                    currentLine--;
                    currentPos = lstrlen(str[currentLine]);
                    //str[currentLine][currentPos] = '\0';
                }
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        else if (currentPos < 30) {
            if (currentLine < 10 && currentPos < 30) {
                str[currentLine][currentPos++] = wParam;
                str[currentLine][currentPos] = '\0';
            }
        }
        else if (currentPos >= 30) {
            if (currentLine < 9) {
                currentLine++;
                currentPos = 0;
                SetCaretPos(0, (currentLine)*size.cy);
            }
            else {
                currentLine = 0;
                currentPos = 0;
                SetCaretPos(0, 0);
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
    break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        for (int i = 0; i <= currentLine; ++i) {
            GetTextExtentPoint32(hDC, str[i], lstrlen(str[i]), &size);
            TextOut(hDC, 0, i * size.cy, str[i], lstrlen(str[i]));
        }
        SetCaretPos(size.cx, currentLine * size.cy);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, IParam);
}