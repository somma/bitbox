/**
 * @file    svc_engine.h
 * @brief   
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.03.06 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once
#include <memory>
#include "conf.h"


typedef class BCSvc : public IBCConf
{
private:
    SC_HANDLE _scm_handle;
public:
    BCSvc() : _scm_handle(NULL)
    {
    }
    virtual ~BCSvc()
    {
        finalize();
    }

    /// @brief 
    bool initialize()
    {
        if (NULL != _scm_handle) return true;

        _scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
        if (NULL == _scm_handle)
        {
            log_err "OpenSCManagerW() faield. gle = %u", GetLastError() log_end;
            return false;
        }

        return true;
    }

    /// @brief 
	void finalize()
    {
        if (NULL != _scm_handle)
        {
            CloseServiceHandle(_scm_handle);
        }
    }

	BCEngines get_engine_value() { return SVC_ENGINE; }

    /// @brief
	bool is_exists(const char* values, ...)
    {
        _ASSERTE(NULL != _scm_handle);
        if (NULL == _scm_handle)
        {
            log_err "initialize() first..." log_end;
            return false;
        }

        _ASSERTE(NULL != values);
        if (NULL == values) return false;

        bool ret = false;
        SC_HANDLE service_handle = NULL;
#pragma warning(disable: 4127)
        do
        {   
            // already exists?
            service_handle = OpenServiceA(_scm_handle, values, SERVICE_QUERY_CONFIG);
            if (NULL != service_handle)
            {
                ret = true; // found
                break;
            }
        } while (false);
#pragma warning(default: 4127)

        CloseServiceHandle(service_handle);
        return ret;
    };
} *PBCSvc;
