/**
* @file    wmi_engine.h
* @brief
*
* @author  SeongMun, Choi (c1219abc@naver.com)
* @date    2016.03.07 16:46 created.
**/

#pragma once
#include "conf.h"

typedef class BCWmi 
{
private:
	HRESULT m_hr;
	IWbemLocator *mp_loc;
	IWbemServices *mp_svc;
	IEnumWbemClassObject *mp_enumerator;
	IWbemClassObject *mp_cls_obj;
	//wchar_t *m_query_str;
	//wchar_t *m_column_str;
public:
	BCWmi()
	{
		mp_loc = NULL;
		mp_svc = NULL;
		mp_enumerator = NULL;
		mp_cls_obj = NULL;
	}

	virtual ~BCWmi()
	{
		finalize();
	}
	/// @brief 
	bool initialize()
	{

	}

	/// @brief 
	void finalize()
	{

	}

	/// @brief
	bool is_wmi_exists()
	{

	}
} *PBCWmi;

/*
class wmi_engine
{
public:
	wmi_engine();
	~wmi_engine();
};

wmi_engine::wmi_engine()
{
}


wmi_engine::~wmi_engine()
{
}
*/