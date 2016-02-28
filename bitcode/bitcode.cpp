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

/// @brief entry point
int main()
{
    set_log_format(false, false, true);

    BCConf _conf;
    _conf.load_config(L"z:\\work.bob\\bob4-3-antivm\\bitbox\\bitcode\\bitcode.conf");

    // check registries
    BCReg _reg_engine;
    for (auto reg_info : _conf._regs)
    {
        if (true == _reg_engine.is_exists(reg_info))
        {
            log_info "[found]" log_end;
            reg_info.dump();
        }
    }

    log_info "press any key to terminate..." log_end;
    _pause;

    return 0;
}

