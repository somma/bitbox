/**
 * @file    reg_engine.h
 * @brief
 *
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.02.28 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once
#include "conf.h"
#include "RegistryUtil.h"


typedef class BCReg : public IBCConf
{
private:
	std::wstring _key_name;
	std::wstring _val_name;
	std::wstring _val_data;

public:
	BCReg() {}
	virtual ~BCReg() {}

	bool initialize() { return true; }
	void finalize() { return; }
	BCEngines get_engine_value() { return REG_ENGINE; }

	/// @brief  reg_info 를 통해 해당 키/밸류/데이터가 존재하면
	///         true 를 리턴한다. 
	bool is_exists(const char* values, ...)
	{
		//HKEY key = RUOpenKey(reg_info._root_key.c_str(),
		//                     reg_info._key_name.c_str(),
		//                     true);
		_ASSERTE(NULL != values);
		if (NULL == values) return false;

		va_list list;
		va_start(list, values);

		_key_name = MbsToWcsEx(values);
		_val_name = MbsToWcsEx(va_arg(list, const char*));
		_val_data = MbsToWcsEx(va_arg(list, const char*));

		va_end(list);

		std::wstring data;
		if (true == RUReadString(HKEY_LOCAL_MACHINE, _key_name.c_str(), _val_name.c_str(), data))
		{
			//log_info "%s", data.c_str() log_end;

			if (std::wstring::npos != data.find(_val_data.c_str()))
			{
				return true;    // ok, we got!
			}
		}

		return false;
	}
} *PBCReg;