#include <windows.h>
#include <tchar.h>
#include <time.h>
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
  static TCHAR str[10][101];
  static int count_x, count_y;
  RECT rt = { 0,0, 5000, 5000 };
  
  //srand(time(NULL));

  switch (iMsg)
  {
  case WM_CREATE:
    count_x = 0;
    count_y = 0; 
    break;
  case WM_PAINT:
    int idx;
    hdc = BeginPaint(hwnd, &ps);

    //for (idx = 0; idx <= count_y; idx++)
      DrawText(hdc, str[0], _tcslen(str[0]), &rt, NULL);
    
    EndPaint(hwnd, &ps);
    break;
  case WM_CHAR:
    str[count_y][count_x++] = wParam;
    str[count_y][count_x] = '\0';

    if (count_x > 99)
    {
      str[count_y][count_x] = '\n';

      count_y++;
      count_x = 0;
    }

    InvalidateRgn(hwnd, NULL, TRUE);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
