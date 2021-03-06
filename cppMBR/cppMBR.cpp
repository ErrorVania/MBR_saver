﻿#include "stdafx.h"
#include <Windows.h>
#include <iostream>


int main()
{
	DWORD mbrsize = 512;
	DWORD c;
	HANDLE MBRhandle = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (MBRhandle == INVALID_HANDLE_VALUE) {
		CloseHandle(MBRhandle);
		return EXIT_FAILURE;
	}

	byte *mbr = new byte[mbrsize];
	ReadFile(MBRhandle,mbr,mbrsize,&c,0);

	std::cout << "Opened Handle: 0x" << &MBRhandle << std::endl;
	std::cout << "Bytes Read: " << c << std::endl;
	CloseHandle(MBRhandle);
	
	std::cout << "Writing to file...";
	HANDLE newHandle = CreateFile(TEXT("MBR.bin"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(newHandle,mbr,512,&c,0);
	std::cout << "DONE" << std::endl;
	CloseHandle(newHandle);
    return 0;
}

