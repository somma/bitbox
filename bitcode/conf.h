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
            "[Detected Registry] = Root_Key : %s, Sub_Key : %s, Val_Name : %s, Val_Data : %s", 
            _root_key.c_str(),
            _key_name.c_str(),
            _val_name.c_str(),
            _val_data.c_str()
        log_end
    }
} *PRegInfo;

typedef class DeviceInfo
{
public:
	DeviceInfo(_In_ const char* root_key,
		_In_ const char* key_name)
		: _root_key(root_key),
		_key_name(key_name)
	{
	}

	std::string _root_key;
	std::string _key_name;

	void dump()
	{
		log_info
			"[Detected Device] = Root_Key : %s, Sub_Key : %s, Val_Name : %s",
			_root_key.c_str(),
			_key_name.c_str()
			log_end
	}
} *PDeviceInfo;

/*
 * BitBox config/detect pattern class
 */
typedef class BCConf
{
public:
    bool load_config(_In_ const wchar_t* config_path);

	std::list<RegInfo>			_regs;
	std::map<BC_ENGINE_TYPE, std::list<std::string>> _conf_value;

private:
    std::list<std::string>      _conf_list;

} *PBCConf;

