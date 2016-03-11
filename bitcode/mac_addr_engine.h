/**
* @file    mac_addr_engine.h
* @brief
* @author  Hojei, Yu (hojei1452@gmail.com)
* @date    2016.03.10 23:11 created.
* @copyright All rights reserved by Hojei, Yu
**/
#pragma once
#include "conf.h"
#include "MacUtil.h"

typedef class BCMac : public IBCEngine
{
private:
	std::list<std::string> _mac_addr;

public:
	BCMac()
	{

	}
	virtual ~BCMac()
	{

	}

	bool initialize()
	{
		Mac mac;
		return (mac.getMacList(_mac_addr));
	}
	void finalize() { return; }
	BC_ENGINE_TYPE get_engine_type() { return MAC_ENGINE; }

	/// @brief
	bool is_exists(const char* values, ...)
	{
		_ASSERTE(NULL != values);
		if (NULL == values) return false;

		for (auto _mac_addrs : _mac_addr)
		{
			if (std::string::npos != _mac_addrs.find(values))
			{
				return true;    // ok, we got!
			}
		}
		return false;
	}

	void dump(const char* values)
	{
		log_info "[Detected Mac Address] = %s:xx:xx:xx", values log_end;
	}
} *PBCMac;