 #pragma once

#include <Windows.h>
#include <vector>

class cMemory {
public:
	cMemory();
	~cMemory();

	template <class ValueType>
	ValueType ReadMemory(DWORD Address) {
		ValueType Value;
		ReadProcessMemory(ProcessHandle, (LPBYTE*)Address, &Value, sizeof(Value), NULL);
		return Value;
	}

	template <class ValueType>
	ValueType WriteMemory(DWORD Address, ValueType Value) {
		WriteProcessMemory(ProcessHandle, (LPBYTE*)Address, &Value, sizeof(Value), NULL);
		return 0;
	}

	DWORD FindProcess(const char*);
	DWORD FindAddress(DWORD, std::vector<DWORD>);

	uintptr_t FindModule(const char*);
	uintptr_t GetModuleBaseAddress(const char*);

	DWORD ProcessID;
	HANDLE ProcessHandle;
};

extern cMemory Memory;
