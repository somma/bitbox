/**----------------------------------------------------------------------------
 * log.h
 *-----------------------------------------------------------------------------
 * initialize_log() 함수를 명시적으로 호출하면
 *	- log level, log target (file, debugger, console, etc) 지정/변경 가능
 *	- log format 지정/변경 가능
 *  - multi thread 환경에서 serialization 이 됨
 *
 * log_err, con_err 같은 매크로만 사용하면 
 *	- debugger, console 로 메세지 출력 가능
 *-----------------------------------------------------------------------------
 * All rights reserved by Noh,Yonghwan (fixbrain@gmail.com, unsorted@msn.com)
 *-----------------------------------------------------------------------------
 * 2015:1:12 15:26 created
**---------------------------------------------------------------------------*/
#ifndef _log_h_
#define _log_h_

#pragma warning(disable:4005)


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sal.h>

/// @brief log level
#define log_level_debug         0
#define log_level_info          1
#define log_level_warn          2
#define log_level_critical      3
#define log_level_error         log_level_critical

//
// C like APIs
//

void
set_log_format(
	_In_ bool show_process_name, 
	_In_ bool show_pid_tid,
	_In_ bool show_function_name
	);

void
log_write_fmt(
    _In_ uint32_t log_level,
	_In_z_ const char* function,
    _In_z_ const char* fmt, 
    _In_ ...
    );


//
// define macro for convenience
//
#define log_err		log_write_fmt( log_level_error, __FUNCTION__, 
#define log_warn	log_write_fmt( log_level_warn, __FUNCTION__,  
#define log_info	log_write_fmt( log_level_info, __FUNCTION__, 
#define log_dbg		log_write_fmt( log_level_debug, __FUNCTION__, 

#define log_end		);

#endif//_log_h_