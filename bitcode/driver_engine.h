/**
* @file    driver_engine.h
* @brief
* @author  Hojei, Yu (hojei1452@gmail.com)
* @date    2016.03.10 23:11 created.
* @copyright All rights reserved by Hojei, Yu
**/
#pragma once
#include "conf.h"

typedef class BCDriver : public IBCEngine
{
private:
	HANDLE _driver_hendle;

public:
	BCDriver()
	{

	}
	virtual ~BCDriver()
	{

	}

	bool initialize() { return true; }
	void finalize() { return; }
	BC_ENGINE_TYPE get_engine_type() { return DRIVER_ENGINE; }

	/// @brief
	bool is_exists(const char* values, ...)
	{
		_ASSERTE(NULL != values);
		if (NULL == values) return false;

		_driver_hendle = CreateFileA(
			values,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);

		if (_driver_hendle != INVALID_HANDLE_VALUE)
			return true;

		return false;
	}

	void dump(const char* values)
	{
		log_info "[Detected Driver] = %s", values log_end;
	}

} *PBCDriver;

