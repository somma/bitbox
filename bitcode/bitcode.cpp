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
    set_log_format(false, false, false);

    BCConf _conf;
    _conf.load_config(L"..\\bitcode\\bitcode.conf");

	std::list<IPBCConf> _iconf;
	_iconf.push_back(new BCFile);
	_iconf.push_back(new BCSvc);
	_iconf.push_back(new BCProcs);
	_iconf.push_back(new BCReg);

	for (auto engine : _iconf)
	{
		if (true != engine->initialize())
		{
			log_err "initialize() failed." log_end;
			return -1;
		}

		BCEngines engine_num = engine->get_engine_value();
		if (engine_num == REG_ENGINE)
		{
			for (auto reg_info : _conf._regs)
			{
			    if (true == engine->is_exists(
					reg_info._key_name.c_str(),
					reg_info._val_name.c_str(),
					reg_info._val_data.c_str()))
			    {
			        reg_info.dump();
			    }
			}
		}
		else
		{
			std::map<BCEngines, std::list<std::string>>::iterator it = _conf._conf_value.find(engine_num);
			if (it == _conf._conf_value.end())
			{
				log_err "not found map." log_end;
				return -1;
			}
			for (auto names : it->second)
			{
			    if (true == engine->is_exists(names.c_str()))
			    {
			        log_info "[Detected] = %s", names.c_str() log_end;
			    }
			}
		}
	}

    log_info "press any key to terminate..." log_end;
    _pause;

    return 0;
}

