#include <windows.h>
#include <windowsx.h>
#include <string>
#include<TlHelp32.h>
#include<sysinfoapi.h>
HDC hdcCompatible;

#pragma comment(linker, "/entry:WinMainCRTStartup")
HINSTANCE hst;
int Height, width;
DWORD64 FindProcess(char*name)
{
	HANDLE handle_process = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	if (Process32First(handle_process, &process))
	{
		while (Process32Next(handle_process, &process))
		{
			if(!strcmp(name,process.szExeFile))
			{
				return process.th32ProcessID;
			}
		}
	}
	return 0;
}
void InjectDLL(DWORD64 pID)
{
	char path[256] = "C:\\Rost\\dll_den_Rost.dll";//E:\\repos\\InnenProgrammeRost\\x64\\Debug\\dll_den_Rost.dll C:\\Rost\\dll_den_Rost.dll
	LPVOID remstring;
	LPCVOID loadlib;
	HANDLE dll_hanlde = OpenProcess(PROCESS_ALL_ACCESS,0,pID);
	loadlib = (LPVOID)(GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"));
	remstring = (LPVOID)(VirtualAllocEx(dll_hanlde, 0, strlen(path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	WriteProcessMemory(dll_hanlde, (LPVOID)remstring, path, strlen(path), 0);
	CreateRemoteThread(dll_hanlde, 0, 0, (LPTHREAD_START_ROUTINE)loadlib, remstring, 0, 0);
	CloseHandle(dll_hanlde);
}
void dllStart()
{
	DWORD64 pID;
	char proc_name[256] = "RustClient.exe";
	pID = FindProcess(proc_name);
	InjectDLL(pID);
	printf("pID: %x \n",pID);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hMemDcFrame, hDC;
	static HBITMAP hBmpFrame;
	RECT rect;

	static int len;
	static LOGFONT lFont;
	static HFONT hFont, hOldFont;
	switch (msg) {
	case WM_ERASEBKGND:
		return true;
	case WM_CREATE:
		
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hMemDcFrame = CreateCompatibleDC(hDC); // DC в памяти
		hBmpFrame = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		SelectObject(hMemDcFrame, hBmpFrame);
		
		
		
		break;
	case WM_SIZE:
		
		GetClientRect(hWnd, &rect);
		hBmpFrame = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		DeleteObject(SelectObject(hMemDcFrame, hBmpFrame)); // пересоздаем буфер
		break;

		InvalidateRect(hWnd, NULL, false);
		
		break;
	case WM_PAINT:
		
		
		hDC = BeginPaint(hWnd, &ps);// DC окна
		GetClientRect(hWnd, &rect);
		FillRect(hMemDcFrame, &rect, GetStockBrush(BLACK_BRUSH)); // Закрашиваем буфер
		hOldFont = (HFONT)SelectObject(hMemDcFrame, CreateFontIndirect(&lFont));
	
		BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDcFrame, 0, 0, SRCCOPY); // копируем буфер на экран
		DeleteObject(SelectObject(hMemDcFrame, hOldFont));
		
		
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		ReleaseDC(hWnd, hDC);
		DeleteDC(hMemDcFrame);
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;
}


int frequency_of_primes(int n) {
	int i, j;
	int freq = n - 1;
	for (i = 2; i <= n; ++i) for (j = (int)sqrt((double)i); j > 1; --j) if (i%j == 0) { --freq; break; }
	return freq;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	
	MSG msg;
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszClassName = "FensterdenMalerungd";
	wc.lpszMenuName = "FensterdenMalerungd";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	width = GetSystemMetrics(SM_CXSCREEN);
	Height = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = CreateWindow("FensterdenMalerungd", "FensterdenMalerungd", WS_EX_TOPMOST | WS_POPUP, 0, 0, width, Height, NULL, NULL, hInst, NULL);

	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 70, LWA_ALPHA);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	ShowWindow(hWnd, nCmd);
	
	dllStart();
	while (GetMessage(&msg, NULL, 0, 0)) {

		//UpdateWindow(hWnd);
		

	//	const double maxFPS = 60.0;
	//	const double maxPeriod = 1.0 / maxFPS;

		// approx ~ 16.666 ms

	//	QueryPerformanceCounter((LARGE_INTEGER*)&frameEnd);
	//	elapsedTime = ElapsedMicroseconds(frameStart, frameEnd);
		//Sleep(300);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		 Sleep(120);
		InvalidateRect(hWnd, NULL, 1);
	/*
		DWORD currentTime = GetTickCount();

		DWORD m_startTime =0;
		if (m_startTime == 0) {
			m_startTime = currentTime;
		}
		float t = 2 * ((currentTime - m_startTime) % 300) / 300.0f;
		if (t > 1.0f) {
			
			t = 2 - t;
		}
		
		*/
	}

	


	return 0;
}
int  k = 0;
