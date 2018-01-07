#include <windows.h>
#include <tchar.h>
#include <math.h>

#define BSIZE 40

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

double LengthPts(int x1, int y1, int x2, int y2)
{
  return(sqrt(((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
  if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
  else return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
  static int startX, startY, oldX, oldY;
  static BOOL Drag;
  int endX, endY;

  switch (iMsg)
  {
  case WM_CREATE:
    startX = oldX = 50;
    startY = oldY = 50;
    Drag = FALSE;
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    
    MoveToEx(hdc, startX, startY, NULL);
    LineTo(hdc, oldX, oldY);

    EndPaint(hwnd, &ps);
    break;

  case WM_LBUTTONDOWN:
    Drag = TRUE;
    break;

  case WM_LBUTTONUP:
    Drag = FALSE;
    break;

  case WM_MOUSEMOVE:
    hdc = GetDC(hwnd);
    if (Drag)
    {
      SetROP2(hdc, R2_XORPEN);
      SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
      endX = LOWORD(lParam);
      endY = HIWORD(lParam);
      MoveToEx(hdc, startX, startY, NULL);
      LineTo(hdc, oldX, oldY); // 기존에 그러졌던 까만 선이 흰색선과 만나서 흰색이 됨. 없어지는 걸로 보임
      MoveToEx(hdc, startX, startY, NULL);
      LineTo(hdc, endX, endY); // 배경이 흰색이므로 흰색 xor 흰색하면 검은색 선이 만들어진다.
      oldX = endX; oldY = endY;
    }
    ReleaseDC(hwnd, hdc);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
