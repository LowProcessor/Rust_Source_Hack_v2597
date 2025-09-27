#pragma once
#include<string>
using namespace std;
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\d3d9.lib") 
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\d3dx9.lib")
#include <d3d9.h>
#include "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include\d3dx9.h"

int WIDTH = GetSystemMetrics(SM_CXSCREEN), HEIGHT = GetSystemMetrics(SM_CYSCREEN);

#include <Windows.h>
#include <windowsx.h>
#include <sstream>
#include <iostream> 
#include <math.h>  

#include <vector>
#include <algorithm>   

using namespace std;



RECT m_Rect;
HDC HDC_Desktop;
HBRUSH ESP_FARBEN;
HFONT hOldFont;
LOGFONT Font;
HWND TargetWnd;
HWND Handle;
PAINTSTRUCT ps;


void SetzenFarbenESP_BOX_Spieler(HDC hDesktop, HWND handle)
{
	HDC_Desktop = hDesktop;
	Handle = handle;
	ESP_FARBEN = CreateSolidBrush(RGB(255, 0, 0));
}



void DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(HDC_Desktop, &rect, ESP_FARBEN);
}
void DrawText_W(int x,int y, string text)
{
	RECT rect = { x,y,x + 80,y + 30 };
	SetBkMode(HDC_Desktop, TRANSPARENT);
	DrawText(HDC_Desktop, text.c_str(), strlen(text.c_str()), &rect, DT_CENTER);
}
void BOX_ESP(int x, int y, int w, int h, int thickness)
{
	DrawFilledRect(x, y, w, thickness);
	DrawFilledRect(x, y, thickness, h);
	DrawFilledRect((x + w), y, thickness, h);
	DrawFilledRect(x, y + h, w + thickness, thickness);
}
HWND ESP_WIN = FindWindow(0, "FensterdenMalerungd");
void ESP_HP_oder_Distantion(int x, int y, float HP)
{


	//GetWindowRect(ESP_WIN, &m_Rect);
/*	hDC = BeginPaint(TargetWnd, &ps); // DC окна
	GetClientRect(TargetWnd, &m_Rect);
	FillRect(hMemDcFrame, &m_Rect, GetStockBrush(WHITE_BRUSH)); // Закрашиваем буфер
	hOldFont = (HFONT)SelectObject(hMemDcFrame, CreateFontIndirect(&Font));

		DrawText(hMemDcFrame, to_string(HP).c_str(), strlen(to_string(HP).c_str()), &m_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // выводим текст в буфер

	BitBlt(hDC, 0, 0, m_Rect.right, m_Rect.bottom, hMemDcFrame, 0, 0, SRCCOPY); // копируем буфер на экран
	DeleteObject(SelectObject(hMemDcFrame, hOldFont));
	EndPaint(TargetWnd, &ps);
	*/

	GetWindowRect(TargetWnd, &m_Rect);
	DrawText_W(x, y, to_string(HP));
	//	DrawText_W(x, y, D3DCOLOR_ARGB(255, 0, 255, 0, 0), TEXT_FONT, to_string(HP));
}
void IDX_PRINT(int x, int y, int HP)
{


	//GetWindowRect(ESP_WIN, &m_Rect);
/*	hDC = BeginPaint(TargetWnd, &ps); // DC окна
	GetClientRect(TargetWnd, &m_Rect);
	FillRect(hMemDcFrame, &m_Rect, GetStockBrush(WHITE_BRUSH)); // Закрашиваем буфер
	hOldFont = (HFONT)SelectObject(hMemDcFrame, CreateFontIndirect(&Font));

		DrawText(hMemDcFrame, to_string(HP).c_str(), strlen(to_string(HP).c_str()), &m_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // выводим текст в буфер

	BitBlt(hDC, 0, 0, m_Rect.right, m_Rect.bottom, hMemDcFrame, 0, 0, SRCCOPY); // копируем буфер на экран
	DeleteObject(SelectObject(hMemDcFrame, hOldFont));
	EndPaint(TargetWnd, &ps);
	*/

	GetWindowRect(TargetWnd, &m_Rect);
	DrawText_W(x, y, to_string(HP));
	//	DrawText_W(x, y, D3DCOLOR_ARGB(255, 0, 255, 0, 0), TEXT_FONT, to_string(HP));
}




/*
LPDIRECT3DDEVICE9 d3d_device;

LPD3DXFONT TEXT_FONT;
void init_d3d(HWND hwnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS presentParametr;
	ZeroMemory(&presentParametr, sizeof(presentParametr));

	presentParametr.Windowed = 1;
	presentParametr.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParametr.hDeviceWindow = hwnd;
	presentParametr.BackBufferFormat = D3DFMT_A8R8G8B8;
	presentParametr.BackBufferWidth = WIDTH;
	presentParametr.BackBufferHeight = HEIGHT;
	presentParametr.EnableAutoDepthStencil = 1;
	presentParametr.AutoDepthStencilFormat = D3DFMT_D16;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presentParametr, &d3d_device);
	D3DXCreateFont(d3d_device, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &TEXT_FONT);
}
void DrawText_W(int x, int y, DWORD color, LPD3DXFONT font, string str)
{
	RECT text_pos = { x,y,x + 120,y + 16 };
	font->DrawText(0, str.c_str(), -1, &text_pos, DT_NOCLIP | DT_CENTER, color);
}
void DrawBox(int x, int y, int shirina, int visota, int px, DWORD color)
{
	ID3DXLine* line;
	D3DXCreateLine(d3d_device, &line);
	D3DXVECTOR2 Kwadratik[5];
	Kwadratik[0] = { D3DXVECTOR2(x,y) };
	Kwadratik[1] = { D3DXVECTOR2(x + shirina,y) };
	Kwadratik[2] = { D3DXVECTOR2(x + shirina,y + shirina) };
	Kwadratik[3] = { D3DXVECTOR2(x,y + visota) };
	Kwadratik[4] = { D3DXVECTOR2(x,y) };
	line->SetWidth(px);
	line->Begin();
	line->Draw(Kwadratik, 5, color);
	line->End();
	line->Release();
}
*/