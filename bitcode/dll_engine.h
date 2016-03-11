#pragma once
#include "stdafx.h"
#include "log.h"

typedef class BCdll 
{
private:
	DWORD pid;
	HANDLE hProcess;

public:
	BCdll() 
	{
		pid = NULL;
		hProcess = NULL;
	};
	virtual ~BCdll() 
	{
	
	};

	bool initialize() 
	{
		pid = GetCurrentProcessId();
		if (pid == NULL)
		{
			log_err "GetCurrentProcessId() failed." log_end;
			return false;
		}

		hProcess = OpenProcess(
			PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE,
			pid);
		if (NULL == hProcess)
		{
			log_err "OpenProcess() failed. gle = %u ", GetLastError() log_end;
			return false;
		}

		return true;
	};

	void finalize() 
	{
		CloseHandle(hProcess);
	};

	bool is_exists(const char* values, ...)
	{
		HMODULE hMods[1024];
		DWORD cbNeeded;
		unsigned int i;

		wchar_t *val = MbsToWcs(values);
		

		if ( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded) ) 
		{

			for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
			{
				TCHAR szModName[MAX_PATH];

				if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
				{
					if (wcsstr(szModName, val) != NULL) 
					{
						return true;
					}
				}
			}

		}
		return false;
	}; 
};
