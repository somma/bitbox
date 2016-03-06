/**
 * @file    bitcode.cpp
 * @brief   This file contains entry point of ths SW.
 *
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.02.28 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#include "stdafx.h"
#include "log.h"
#include "conf.h"
#include "util.h"
#include "reg_engine.h"
#include "file_engine.h"
#include "svc_engine.h"
#include "proc_engine.h"

/// @brief entry point
int main()
{
    set_log_format(false, false, true);

    BCConf _conf;
    _conf.load_config(L"z:\\work.bob\\bob4-3-antivm\\bitbox\\bitcode\\bitcode.conf");

    BCReg _reg_engine;
    BCFile _file_engine;
    BCSvc _svc_engine;
    BCProcs _proc_engine;
    
    if (true != _svc_engine.initialize())
    {
        log_err "BCSvc::initialize() failed." log_end;
        return -1;
    }

    if (true != _proc_engine.initialize())
    {
        log_err "BCProc::initialize() failed." log_end;
        return -1;
    }

    // check registries
    for (auto reg_info : _conf._regs)
    {
        if (true == _reg_engine.is_exists(reg_info))
        {
            log_info "[found]" log_end;
            reg_info.dump();
        }
    }

    // file check
    for (auto file_info : _conf._file_names)
    {
        if (true == _file_engine.is_file_exists(file_info.c_str()))
        {
            log_info "[found] file = %s", file_info.c_str() log_end;
        }
    }

    // service check
    for (auto svc_name : _conf._svc_names)
    {
        if (true == _svc_engine.is_svc_exists(svc_name.c_str()))
        {
            log_info "[found] service = %s", svc_name.c_str() log_end;
        }
    }

    // process check
    for (auto proc_name : _conf._proc_names)
    {
        if (true == _proc_engine.is_process_exists(proc_name.c_str()))
        {
            log_info "[found] process = %s is running", proc_name.c_str() log_end;
        }
    }

    log_info "press any key to terminate..." log_end;
    _pause;

    return 0;
}

