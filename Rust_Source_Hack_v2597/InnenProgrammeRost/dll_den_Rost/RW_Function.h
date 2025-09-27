#pragma once
#include <Windows.h>  
#include <TlHelp32.h>
#include <iostream>
#include <io.h>
#include"Offsets.h"
#pragma warning(disable:4996)
char proc_name[256] = RustClient_exe;
char mod_game_assembley[256] = GameAssembly_dll;
char mod_unity_player[256] = UnityPlayer_dll;


DWORD64 RClient_pID = 0;
DWORD64 GameAssembleyBaseAddress=0;
DWORD64 UnityPlayerBaseAddress=0;
template <typename T>
T read(DWORD64 addr)
{
	T*l = (T*)(addr);
	return *l;
}

template <typename T>
void write(DWORD64 addr, T wert)
{

	T*l = (T*)(addr);
	*l = wert;
	
}
void GetAllModBaseAddr()
{

	RClient_pID = (DWORD64)GetModuleHandle(proc_name);
	printf("RClient_pID: %x \n", RClient_pID);
	 GameAssembleyBaseAddress = (DWORD64)GetModuleHandle(mod_game_assembley);
	 printf("GameAssembleyBaseAddress: %x \n", GameAssembleyBaseAddress);
	UnityPlayerBaseAddress = (DWORD64)GetModuleHandle(mod_unity_player);
	printf("UnityPlayerBaseAddress: %x \n", UnityPlayerBaseAddress);
}
