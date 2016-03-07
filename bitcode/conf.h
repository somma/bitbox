/**
 * @file    conf.h
 * @brief   
 *
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.02.28 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once

#include <sal.h>
#include <string>
#include <list>
#include <map>
#include "log.h"

typedef class RegInfo
{
public:
    RegInfo(_In_ const char* root_key, 
            _In_ const char* key_name,
            _In_ const char* val_name,
            _In_ const char* val_data)
        : _root_key(root_key),
        _key_name(key_name),
        _val_name(val_name),
        _val_data(val_data)
    {
    }

    std::string _root_key;
    std::string _key_name;
    std::string _val_name;
    std::string _val_data;

    void dump()
    {
        log_info 
            "[Detected] = Root_Key : %s, Sub_Key : %s, Val_Name : %s, Val_Data : %s", 
            _root_key.c_str(),
            _key_name.c_str(),
            _val_name.c_str(),
            _val_data.c_str()
        log_end
    }
} *PRegInfo;

typedef enum BCEngines
{
	FILE_ENGINE,
	PROC_ENGINE,
	SVC_ENGINE,
	REG_ENGINE
} *PBCEngines;

typedef class BCConf
{
public:
    bool load_config(_In_ const wchar_t* config_path);

	std::list<RegInfo>			_regs;
	std::map<BCEngines, std::list<std::string>> _conf_value;

private:
    std::list<std::string>      _file_names;
    std::list<std::string>      _svc_names;
    std::list<std::string>      _proc_names;

} *PBCConf;


typedef class IBCConf
{
public:
	virtual bool initialize() = 0;
	virtual void finalize() = 0;
	virtual BCEngines get_engine_value() = 0;
	virtual bool is_exists(const char* values, ...) = 0;
} *IPBCConf;
