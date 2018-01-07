#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
  HWND hwnd;
  MSG msg;
  WNDCLASS WndClass;
  WndClass.style = CS_HREDRAW | CS_VREDRAW;
  WndClass.lpfnWndProc = WndProc;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hInstance = hInstance;
  WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  WndClass.lpszMenuName = NULL;
  WndClass.lpszClassName = _T("Window Class Name");
  RegisterClass(&WndClass);

  hwnd = CreateWindow(_T("Window Class Name"),
    _T("Window Title Name"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hwnd, nCmdShow);

  UpdateWindow(hwnd);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
  HBRUSH hBrush, oldBrush;

  switch (iMsg)
  {
  case WM_CREATE:
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    Rectangle(hdc, 100, 200, 150, 300);
    TextOut(hdc, 110, 250, _T("왼쪽"), _tcslen("왼쪽"));
    Rectangle(hdc, 150, 200, 200, 300);
    Rectangle(hdc, 150, 100, 200, 200);
    TextOut(hdc, 160, 120, _T("위쪽"), _tcslen("위쪽"));
    Rectangle(hdc, 200, 200, 250, 300);
    TextOut(hdc, 200, 250, _T("오른쪽"), _tcslen("오른쪽"));
    Rectangle(hdc, 150, 300, 200, 400);
    TextOut(hdc, 151, 350, _T("아래쪽"), _tcslen("아래쪽"));
    EndPaint(hwnd, &ps);
    
    break;
  case WM_KEYDOWN:
    if (wParam == VK_LEFT)
    {
      hdc = GetDC(hwnd);
      hBrush = CreateSolidBrush(RGB(255, 0, 0));
      oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
      Rectangle(hdc, 100, 200, 150, 300);
      ReleaseDC(hwnd, hdc);
    }
    else if (wParam == VK_RIGHT)
    {
      hdc = GetDC(hwnd);
      hBrush = CreateSolidBrush(RGB(255, 0, 0));
      oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
      Rectangle(hdc, 200, 200, 250, 300);
      ReleaseDC(hwnd, hdc);
    }
    else if (wParam == VK_UP)
    {
      hdc = GetDC(hwnd);
      hBrush = CreateSolidBrush(RGB(255, 0, 0));
      oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
      Rectangle(hdc, 150, 100, 200, 200);
      ReleaseDC(hwnd, hdc);
    }
    else if (wParam == VK_DOWN)
    {
      hdc = GetDC(hwnd);
      hBrush = CreateSolidBrush(RGB(255, 0, 0));
      oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
      Rectangle(hdc, 150, 300, 200, 400);
      ReleaseDC(hwnd, hdc);
    }
 
    break;
  case WM_KEYUP:
    InvalidateRgn(hwnd, NULL, TRUE);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
