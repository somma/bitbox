/**
* @file    wmi_engine.h
* @brief
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
		if (NULL != mp_loc) return false;

		if (S_OK == m_hr) m_hr = Bb_init_com();
		if (S_OK == m_hr) m_hr = Bb_init_com_security();
		if (S_OK == m_hr) m_hr = Bb_init_wmi_locator();
		if (S_OK == m_hr) m_hr = Bb_wmi_con_service();
		if (S_OK == m_hr) m_hr = Bb_wmi_service_on_proxy();
		
		if (S_OK != m_hr)
		{
			log_err "WMI initialize() failed. gle = %u", m_hr log_end;
			return false;
		}
		return true;
	}

	/// @brief 
	void finalize()
	{
		if (mp_loc != NULL) mp_loc->Release();
		if (mp_svc != NULL) mp_svc->Release();
		if (mp_enumerator != NULL) mp_enumerator->Release();
		if (mp_cls_obj != NULL) CoUninitialize();
	}

	/// @brief
	bool is_wmi_exists(_In_ const wchar_t *query_str)
	{
		_ASSERTE(NULL != mp_svc);
		if (NULL == mp_svc)
		{
			log_err "initialize() first..." log_end;
			return false;
		}
		_ASSERTE(NULL != query_str);
		if (NULL == query_str) return false;
		
		HRESULT hr;
		ULONG uRet = 0;
		hr = mp_svc->ExecQuery(
			(BSTR)L"WQL",
			(BSTR)query_str,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&mp_enumerator);

		if (S_OK != hr)
		{
			log_err "ExecQuery() Error..." log_end;
			return false;
		}

		if (NULL != mp_enumerator) {
			mp_enumerator->Next(WBEM_INFINITE, 1, &mp_cls_obj, &uRet);
			if (NULL != mp_cls_obj) {
				mp_cls_obj->Release();
				return true;
			}
		}
		return false;
	}

private:
	HRESULT Bb_init_com() 
	{
		return CoInitializeEx(0, COINIT_MULTITHREADED);
	}

	HRESULT Bb_init_com_security()
	{
		return CoInitializeSecurity(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE,
			NULL
			);
	}

	HRESULT Bb_init_wmi_locator()
	{
		return CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator,
			(void **)&mp_loc
			);
	}

	HRESULT Bb_wmi_con_service()
	{
		return mp_loc->ConnectServer(
			(BSTR)L"ROOT\\CIMV2",
			NULL,
			NULL,
			0,
			NULL,
			0,
			0,
			&mp_svc
		);
	}

	HRESULT Bb_wmi_service_on_proxy()
	{
		return CoSetProxyBlanket(
			mp_svc,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHZ_NONE,
			NULL,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE
			);
	}
} *PBCWmi;
