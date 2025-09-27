#include"decryption_function.h"
#include"function.h"
void _stdcall haupt_function()
{
	//HWND wind = FindWindow(0, "FensterdenMalerungd");
	//HWND wind = FindWindow(0, "Rust");
	//if (!wind) { return 0; }
	//init_d3d(wind);
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}

	GetAllModBaseAddr();
	TargetWnd = FindWindow(0, "FensterdenMalerungd");
	
	//if (!TargetWnd) { return; }
	HDC HDC = GetDC(TargetWnd);
	SetzenFarbenESP_BOX_Spieler(HDC, TargetWnd);
	SetTextColor(HDC_Desktop, (COLORREF)(CreateSolidBrush(RGB(0, 255, 0))));
	MessageBox(0, "hack_started", "hack_started", MB_OK);
	
	while (1) {
		
		
		ErwerbEntitat();
		system("cls");
	}
	//system("pause");
	
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(haupt_function), hModule, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
