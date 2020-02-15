#pragma once

#include <Windows.h>

class MemManager
{
private:
	DWORD engineDllAddress;
	unsigned char _junk[13];
	HANDLE processHandle;

	DWORD clientPanoramaDllAddress;

public:
	MemManager(HANDLE processHandle, DWORD clientPanoramaDllAddress, DWORD engineDllAddress) 
        : engineDllAddress(engineDllAddress), processHandle(processHandle),
          clientPanoramaDllAddress(clientPanoramaDllAddress) {}

	template <class T>
	T readMem(LPCVOID baseAddr)
	{
		T tmp;
		ReadProcessMemory(processHandle, baseAddr, (LPVOID)&tmp, sizeof(tmp), NULL);
		return tmp;
	}

	template <class T>
	void writeMem(LPVOID baseAddr, T value)
	{
		T tmp = value;
		WriteProcessMemory(processHandle, baseAddr,
			(LPCVOID) &tmp, sizeof(tmp), NULL);
	}

	void setProcessHandle(HANDLE processHandle)
	{
		this->processHandle = processHandle;
	}

	DWORD getClientPanoramaDllAddress()
	{
		return clientPanoramaDllAddress;
	}
};

