/**
 * @file    conf.cpp
 * @brief   
 *
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.02.28 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#include "stdafx.h"
#include "conf.h"
#include "json/json.h"
#include <fstream>


/// @brief  
bool BCConf::load_config(const wchar_t * config_path)
{
    _ASSERTE(NULL != config_path);
    if (NULL == config_path) return false;

    std::ifstream js;
    js.open(config_path, std::ifstream::in);
    if (!js.is_open()) return false;

    Json::Value conf;
    Json::Reader reader;
    if (true != reader.parse(js, conf))
    {
        log_err "%s", reader.getFormattedErrorMessages().c_str() log_end;
        return false;
    }

    // read file_name
    Json::Value file_names = conf["file_name"];
    for (auto file_name : file_names)
    {
        _file_names.push_back(file_name.asString());
    }

    // read registry
    Json::Value reg_keys = conf["reg_key"];
    for (auto reg_key : reg_keys)
    {
        RegInfo ri(
            reg_key["root_key"].asString(),
            reg_key["key_name"].asString(),
            reg_key["val_name"].asString(),
            reg_key["val_data"].asString());
        _regs.push_back(ri);
    }


    // read service
    Json::Value svc_names = conf["svc_name"];
    for (auto svc_name : svc_names)
    {
        _svcs.push_back(svc_name.asString());
    }

    /*
    for (auto file_name : _file_names)
    {
        log_info "file name = %s", file_name.c_str() log_end;
    }
    for (auto svc_name : _svcs)
    {
        log_info "svc name = %s", svc_name.c_str() log_end;
    }
    for (auto reg : _regs)
    {
        reg.dump();
    }*/

    return true;
}
