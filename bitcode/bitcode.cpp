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

/// @brief entry point
int main()
{
    set_log_format(false, false, true);

    BCConf _conf;
    _conf.load_config(L"z:\\work.bob\\bob4-3-antivm\\bitbox\\bitcode\\bitcode.conf");



    log_info "press any key to terminate..." log_end;
    _pause;

    return 0;
}

