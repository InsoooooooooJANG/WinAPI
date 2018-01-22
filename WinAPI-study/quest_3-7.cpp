#include <windows.h>
#include <tchar.h>
#include <math.h>
#define BSIZE 40

double LengthPts(int x1, int y1, int x2, int y2)
{
  return (sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
  if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
  else return FALSE;
}

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
  static int x, y;
  static int old_x, old_y;
  static bool Drag;
  int end_x, end_y;

  int circle_x, circle_y;

  switch (iMsg)
  {
  case WM_CREATE:
    old_x = 20; old_y = 20; x = 20; y = 20;
    Drag = FALSE;
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    Ellipse(hdc, 0, 0, 40, 40);
    EndPaint(hwnd, &ps);
    break;
  case WM_LBUTTONDOWN:
    circle_x = LOWORD(lParam);
    circle_y = HIWORD(lParam);

    if (InCircle(x, y, circle_x, circle_y))
      Drag = TRUE;
    else
      Drag = FALSE;
    break;
  case WM_LBUTTONUP:
    hdc = GetDC(hwnd);
    SetROP2(hdc, R2_XORPEN);
    SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, old_x, old_y);
    ReleaseDC(hwnd, hdc);

    Drag = FALSE;
    break;
  case WM_MOUSEMOVE:
    hdc = GetDC(hwnd);

    if (Drag)
    {
      SetROP2(hdc, R2_XORPEN);
      SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
      end_x = LOWORD(lParam);
      end_y = HIWORD(lParam);
      MoveToEx(hdc, x, y, NULL);
      LineTo(hdc, old_x, old_y); // 이전 직선을 xor 연산하여 삭제
      MoveToEx(hdc, x, y, NULL);
      LineTo(hdc, end_x, end_y);
      old_x = end_x; old_y = end_y;

    }
    ReleaseDC(hwnd, hdc);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
