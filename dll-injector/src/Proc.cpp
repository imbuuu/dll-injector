#include "pch.h"
#include "Proc.h"

DWORD GetProcId(const wchar_t* procName)
{
	DWORD PID = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procName, procEntry.szExeFile))
				{
					PID = procEntry.th32ProcessID;
					break;
				}

			} while (Process32Next(hSnap, &procEntry));
		}
	}

	CloseHandle(hSnap);
	return PID;
}