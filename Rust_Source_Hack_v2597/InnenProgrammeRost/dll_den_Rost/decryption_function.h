#pragma once
#include<Windows.h>
#include<TlHelp32.h>
#include"RW_Function.h"

bool TEST_BITD(uint32_t Value, uint32_t BitPosition) {
	return (Value & (1 << BitPosition)) != 0;
}


uint64_t __fastcall Il2cppGetHandle(int32_t ObjectHandleID) {
	uint64_t rdi_1 = ObjectHandleID >> 3;
	uint64_t rcx_1 = (ObjectHandleID & 7) - 1;
	uint64_t baseAddr = GameAssembleyBaseAddress + il2cpphandle + rcx_1 * 0x28;
	uint32_t limit = read<uint32_t>(baseAddr + 0x10);
	if (rdi_1 < limit) {
		uintptr_t objAddr = read<uintptr_t>(baseAddr);
		uint32_t bitMask = read<uint32_t>(objAddr + ((rdi_1 >> 5) << 2));
		if (TEST_BITD(bitMask, rdi_1 & 0x1f)) {
			uintptr_t ObjectArray = read<uintptr_t>(baseAddr + 0x8) + (rdi_1 << 3);
			return read<BYTE>(baseAddr + 0x14) > 1
				? read<uintptr_t>(ObjectArray)
				: ~read<uint32_t>(ObjectArray);
		}
	}
	return 0;
}

inline auto ClientEntities(uint64_t address)
{
	uint64_t v22 = read<uint64_t>(address + 0x18);
	uint32_t v5 = 2;
	uint32_t v6, v7;
	uint64_t* v4 = &v22;

	do
	{
		v6 = *(DWORD*)v4;
		v4 = (uint64_t*)((char*)v4 + 4);
		*((DWORD*)v4 - 1) = (((v6 ^ 0x94F36EF) << 23) | ((v6 ^ 0x94F36EFu) >> 9)) + 896037734;
		--v5;
	} while (v5);
	v7 = v22;
	return Il2cppGetHandle(v22);
}

inline auto EntityList_parkaa(uint64_t address)
{
	uint64_t v22 = read<uint64_t>(address + 0x18);
	uint32_t v5 = 2;
	uint32_t v6, v7, v8;
	uint64_t* v4 = &v22;
	do
	{
		v6 = *(DWORD*)v4;
		v7 = *((unsigned __int8*)v4 + 3);
		v4 = (uint64_t*)((char*)v4 + 4);
		*((DWORD*)v4 - 1) = (((v6 << 8) | v7) - 290628251) ^ 0x80F050EA;
		--v5;
	} while (v5);
	v8 = v22;
	return Il2cppGetHandle(v22);
}