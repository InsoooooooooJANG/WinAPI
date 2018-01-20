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
  static int catX, catY, mouseX, mouseY;
  static BOOL SquirrelFlag;
  static RECT rectView;
  
  switch (iMsg)
  {
  case WM_CREATE:
    catX = 100; 
    catY = 100;
    mouseX = 0;
    mouseY = 0;
    SquirrelFlag = FALSE;

    GetClientRect(hwnd, &rectView);
    break;
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    TextOut(hdc, catX, catY, _T("°í¾çÀÌ"), _tcslen("°í¾çÀÌ"));

    if (SquirrelFlag)
    {
      TextOut(hdc, mouseX, mouseY, _T("¾ÏÁã"), _tcslen("¾ÏÁã"));
    }

    ReleaseDC(hwnd, hdc);
    break;
  case WM_LBUTTONDOWN:
    mouseX = LOWORD(lParam);
    mouseY = HIWORD(lParam);
    SquirrelFlag = TRUE;

    SetTimer(hwnd, 1, 70, NULL);

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_TIMER:
    if(mouseX != catX && mouseY != catY)
    {
      int x = mouseX - catX;
      int y = mouseY - catY;

      if (x < 0)
        catX -= 10;
      else if(x > 0)
        catX += 10;
      
      if (y < 0)
        catY -= 10;
      else if(y > 0)
        catY += 10;
    }

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_LBUTTONUP:
    SquirrelFlag = FALSE;
    KillTimer(hwnd, 1);

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_MOUSEMOVE:
    if (SquirrelFlag == TRUE)
    {
      mouseX = LOWORD(lParam);
      mouseY = HIWORD(lParam);

      InvalidateRgn(hwnd, NULL, TRUE);
    }
   
    break;
  case WM_DESTROY:
    KillTimer(hwnd, 1);
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
