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
  static int head_x, head_y, tail_x, tail_y, cnt, key; // key 1 : up / key 2 : right / key 3 : down / key 4 : left
  static RECT rectView;
  HPEN hPen, oldPen;

  switch (iMsg)
  {
  case WM_CREATE:
    GetClientRect(hwnd, &rectView);
    tail_x = 20; tail_y = 20; head_x = 60; head_y = 20; cnt = 0; key = 0;
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    Rectangle(hdc, 0, 0, rectView.right - 50, rectView.bottom - 50);

    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    Ellipse(hdc, tail_x - 20, tail_y - 20, tail_x + 20, tail_y + 20);
    SelectObject(hdc, oldPen);
    DeleteObject(hPen);

    hPen = CreatePen(PS_SOLID, 1, RGB(255, 0,0));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    Ellipse(hdc, head_x - 20, head_y - 20, head_x + 20, head_y + 20);
    SelectObject(hdc, oldPen);
    DeleteObject(hPen);

    EndPaint(hwnd, &ps);
    break;
  case WM_KEYDOWN:
    if (wParam == VK_RETURN)
    {
      key = 2;
      SetTimer(hwnd, 1, 200, NULL);
    }
    else if (wParam == VK_RIGHT)
    {
      tail_x = head_x - 40;
      tail_y = head_y;
      key = 2;
    }
    else if (wParam == VK_UP)
    {
      tail_x = head_x;
      tail_y = head_y + 40;

      key = 1;
    }
    else if (wParam == VK_LEFT)
    {
      tail_x = head_x + 40;
      tail_y = head_y;

      key = 4;
    }
    else if (wParam = VK_DOWN)
    {
      tail_x = head_x;
      tail_y = head_y - 40;
    
      key = 3;
    }

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_TIMER:
    if (key == 2)
    {
      tail_x += 40;
      head_x += 40;
      if (head_x + 20 >= rectView.right - 50)
      {
        head_x -= 40;
        tail_x -= 40;
      }
    }
    else if (key == 3)
    {
      head_y += 40;
      tail_y += 40;
      if (head_y + 20 >= rectView.bottom - 50)
      {
        tail_y -= 40;
        head_y -= 40;
      }
    }
    else if (key == 4)
    {
      head_x -= 40;
      tail_x -= 40;
      if (head_x - 20 < rectView.left)
      {
        head_x += 40;
        tail_x += 40;
      }
    }
    else if (key == 1)
    {
      head_y -= 40;
      tail_y -= 40;
      if (head_y - 20 < rectView.top)
      {
        head_y += 40;
        tail_y += 40;
      }
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
