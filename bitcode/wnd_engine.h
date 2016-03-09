/**
* @file    wnd_engine.h
* @brief
* @author  SeongMun, Choi (c1219abc@naver.com)
* @date    2016.03.08 16:06 created.
**/

#pragma once
#include "conf.h"

typedef class BCWnd
{
private:
	HWND _mh_wnd;
	HWND _mh_wnd_cls;
public:
	BCWnd() : _mh_wnd(NULL), _mh_wnd_cls(NULL)
	{

	}

	virtual ~BCWnd()
	{
		finalize();
	}

	/// @brief 
	void finalize() 
	{
		if (NULL != _mh_wnd) CloseHandle(_mh_wnd);
		if (NULL != _mh_wnd_cls) CloseHandle(_mh_wnd_cls);
	}

	/// @brief
	bool is_wnd_exists(_In_ const char* wnd_name)
	{
		_ASSERTE(NULL != wnd_name);
		if (NULL == wnd_name) return false;

		_mh_wnd = FindWindowA(NULL, wnd_name);
		_mh_wnd_cls = FindWindowA(wnd_name, NULL);

		if (_mh_wnd || _mh_wnd_cls) return true;
		else false;
	}

} *PBCWnd;