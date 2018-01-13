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
  static int x, y, cnt, key; // key 1 : up / key 2 : right / key 3 : down / key 4 : left
  static RECT rectView;

  switch (iMsg)
  {
  case WM_CREATE:
    GetClientRect(hwnd, &rectView);
    x = 20; y = 20; cnt = 0; key = 0;
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    Rectangle(hdc, 0, 0, rectView.right - 40, rectView.bottom - 40);
    Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
    EndPaint(hwnd, &ps);
    break;
  case WM_KEYDOWN:    
    if (key != 0 && wParam == VK_RETURN)
    {
      cnt++;

      if (cnt % 2 == 1)
        SetTimer(hwnd, 1, 70, NULL);
      else if (cnt % 2 == 0)
        KillTimer(hwnd, 1);
    }
    else if (wParam == VK_RIGHT) 
      key = 2;
    else if (wParam == VK_UP)
      key = 1;
    else if (wParam == VK_LEFT)
      key = 4;
    else if (wParam = VK_DOWN)
      key = 3;

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_TIMER:
    if (key == 2)
    {
      x += 40;
      if (x + 20 > rectView.right - 40) x -= 40;
    }
    else if (key == 3)
    {
      y += 40;
      if (y + 20 > rectView.bottom - 40) y -= 40;
    }
    else if (key == 4)
    {
      x -= 40;
      if (x - 20 < rectView.left) x += 40;
    }
    else if (key == 1)
    {
      y -= 40;
      if (y - 20 < rectView.top) y += 40;
    }
    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_DESTROY:
    KillTimer(hwnd, 1);
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
