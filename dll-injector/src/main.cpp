#include "pch.h"
#include "Proc.h"
#include "File.h"


int main()
{
	// Get File
	std::string filePath;
	const char* cFilePath = nullptr;

	if (GetFilePathFromFileDialog(filePath))
	{
		std::cout << "Selected file: " << filePath << std::endl;

		cFilePath = filePath.c_str();
	}
	else
	{
		std::cout << "File selection canceled." << std::endl;
		return 1;
	}

	// Inject DLL
	DWORD PID = 0;
	
	PID = GetProcId(L"ac_client.exe");

	std::cout << "PID: " << PID << std::endl;

	// Ensure valid process
	if (PID)
	{
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);

		if (hProc != INVALID_HANDLE_VALUE)
		{
			void* ReservedMem = VirtualAllocEx(hProc, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			WriteProcessMemory(hProc, ReservedMem, cFilePath, strlen(cFilePath) + 1, nullptr);

			HANDLE hRemoteThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, ReservedMem, 0, nullptr);

			CloseHandle(hProc);
		}

	}
	else
	{
		std::cout << "Invalid Process\n";
		return 1;
	}

	
	return 0;
}
