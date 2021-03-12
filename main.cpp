#include <windows.h>
#include "save.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG  msg;
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
 	WndClass.lpszClassName = "Window Class Name";
 	RegisterClass(&WndClass);
 	hwnd = CreateWindow("Window Class Name", "notepad", WS_OVERLAPPEDWINDOW,
  	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
  	NULL, NULL, hInstance, NULL);
 	
	ShowWindow(hwnd, nCmdShow);

 	UpdateWindow(hwnd);
 	while(GetMessage(&msg, NULL, 0, 0))
 	{
  		TranslateMessage(&msg);
  		DispatchMessage(&msg);
 	}
 	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
 	HDC   hdc;
 	PAINTSTRUCT ps;          
 	static char str[10][99];
	static int strline[10];
	static int count, line;  	
	static SIZE size;
 	int i;

 	switch(iMsg)
 	{
 		case WM_CREATE:
  			CreateCaret(hwnd, NULL, 4, 20);
  			ShowCaret(hwnd);
  			count = 0;     			
			line = 0;
  			break;              
		case WM_PAINT:
  			hdc = BeginPaint(hwnd, &ps);
  			for(i=0;i<=line;i++)
  			{
  				GetTextExtentPoint(hdc, str[i], strlen(str[i]), &size);
   				TextOut(hdc, 0, i*20, str[i], strlen(str[i])); 
   				SetCaretPos(size.cx, i*20);
  			}
  			EndPaint(hwnd, &ps);
  			break;
 		case WM_CHAR:
  			if(wParam == VK_BACK)
  			{
  				if(count > 0) count--;
				else if(line > 0) count = strline[--line];
			}
  		  	else if(wParam == VK_RETURN) 
  			{
   				if(line<9)        
   				{
   					strline[line] = count;
   					count = 0;
					line++; 
   				}
  			}
  			else if(count<98) str[line][count++] = wParam;
  			str[line][count] = '\0'; 		
			InvalidateRgn(hwnd, NULL, TRUE);
  			break;
 		case WM_DESTROY:
 			char_two str_t;
 			for(i=0;i<10;i++) strcpy(str_t.str[i],str[i]);
 			Save(str_t);
  			HideCaret(hwnd);
  			DestroyCaret();
  			PostQuitMessage(0);
  			break;
	}
 	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
