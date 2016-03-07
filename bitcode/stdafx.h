#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

#include <string>
#include <vector>
#include <list>

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