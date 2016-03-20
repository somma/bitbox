#pragma once

#include "targetver.h"

#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include <conio.h>

#include <string>
#include <vector>
#include <list>

#include <WinSock2.h>
#include <IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib")

#include <sal.h>
#include <windows.h>
#include <strsafe.h>
#include <intsafe.h>
#include <stdint.h>
#include <crtdbg.h>

/**
 * @Purpose Using WMI Provider lib
 * @Quote https://msdn.microsoft.com/ko-kr/library/windows/desktop/aa390423(v=vs.85).aspx
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
**/
#define _WIN32_DCOM
#include <comdef.h>
#include <WbemIdl.h>
#pragma comment(lib, "wbemuuid.lib")

#include "log.h"

/*
 * BitBox Engine type
 */
enum BC_ENGINE_TYPE
{
    FILE_ENGINE = 0,
    PROC_ENGINE = 1,
    SVC_ENGINE  = 2,
    REG_ENGINE  = 3,
	DRIVER_ENGINE = 4,
	MAC_ENGINE = 5,
	CPU_ENGINE = 6
};


/*
 * BitBox Engine Inteface
 */
typedef class IBCEngine
{
public:
    virtual bool initialize() = 0;
    virtual void finalize() = 0;
    virtual BC_ENGINE_TYPE get_engine_type() = 0;
    virtual bool is_exists(const char* values, ...) = 0;
	virtual void dump(const char* values) = 0;
} *PIBCngine;