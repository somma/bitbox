/**----------------------------------------------------------------------------
 * log.cpp
 *-----------------------------------------------------------------------------
 * 
 *-----------------------------------------------------------------------------
 * All rights reserved by Noh,Yonghwan (fixbrain@gmail.com, unsorted@msn.com)
 *-----------------------------------------------------------------------------
 * 2015:1:12 16:54 created
**---------------------------------------------------------------------------*/
#include "stdafx.h"
#include "util.h"
#include "log.h"

/**
 * @brief	
**/
static bool			    _show_process_name = true;
static bool			    _show_pid_tid = true;
static bool			    _show_function_name = true;

/// @brief
void
set_log_format(
	_In_ bool show_process_name, 
	_In_ bool show_pid_tid,
	_In_ bool show_function_name
	)
{
	_show_process_name = show_process_name;
	_show_pid_tid = show_pid_tid;
	_show_function_name = show_function_name;
}

/**
 * @brief	
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
void
log_write_fmt(
    _In_ uint32_t log_level, 
	_In_z_ const char* function,
    _In_z_ const char* fmt, 
    _In_ ...
    )
{
    if (NULL == fmt) return;

	char log_buffer[2048];
    size_t remain = sizeof(log_buffer);
    char* pos = log_buffer;
    va_list args;

    // log level
    switch (log_level)
    {
    case log_level_debug: StringCbPrintfExA(pos, remain, &pos, &remain, 0, "%s", "[DEBG] "); break;
    case log_level_info:  StringCbPrintfExA(pos, remain, &pos, &remain, 0, "%s", "[INFO] "); break;
    case log_level_warn:  StringCbPrintfExA(pos, remain, &pos, &remain, 0, "%s", "[WARN] "); break;
    case log_level_error: StringCbPrintfExA(pos, remain, &pos, &remain, 0, "%s", "[EROR] "); break;
    default:
        _ASSERTE(!"never reach here!");
        return;
    }

    //> show process name
    if (true == _show_process_name)
    {
        StringCbPrintfExA(
            pos, 
            remain, 
            &pos, 
            &remain, 
            0, 
            "%ws",
            get_current_module_fileEx().c_str()
            );
    }

    //> show pid, tid
    if (true == _show_pid_tid)
    {
        StringCbPrintfExA(
            pos,
            remain,
            &pos,
            &remain,
            0,
            "(%+5u:%+5u) : ",
            GetCurrentProcessId(),
            GetCurrentThreadId()
            );
    }

    //> show function name
    if (true == _show_function_name)
    {
        StringCbPrintfExA(pos, remain, &pos, &remain, 0, "%s : ", function);
    }

    va_start(args,fmt);
    HRESULT hRes = StringCbVPrintfExA(
                        pos, 
                        remain, 
                        &pos,
                        &remain,
                        0, 
                        fmt, 
                        args
                        );

    if (S_OK != hRes)
    {
		// invalid character 가 끼어있는 경우 발생 할 수 있음
        StringCbPrintfExA(
            pos, 
            remain, 
            &pos, 
            &remain,
            0, 
            "invalid function call parameters"
            );
    }    
    va_end(args);

    // line feed
    StringCbPrintfExA(pos, remain, &pos, &remain, 0, "\n");

    // Let's write logs.
    switch (log_level)
    {
    case log_level_error: // same as log_level_critical
        write_to_console(wtc_red, log_buffer);
        break;
    case log_level_info:
    case log_level_warn:
        write_to_console(wtc_green, log_buffer);
        break;
    default:
        write_to_console(wtc_none, log_buffer);
    }
           

    OutputDebugStringA(log_buffer);
}
