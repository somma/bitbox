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


typedef class BCReg 
{
public:
    BCReg() {}
    virtual ~BCReg() {}

    /// @brief  reg_info 를 통해 해당 키/밸류/데이터가 존재하면
    ///         true 를 리턴한다. 
    bool is_exists(_In_ RegInfo& reg_info) 
    {
        //HKEY key = RUOpenKey(reg_info._root_key.c_str(),
        //                     reg_info._key_name.c_str(),
        //                     true);
        
        std::wstring data;
        if (true == RUReadString(HKEY_LOCAL_MACHINE,
                                 MbsToWcsEx(reg_info._key_name.c_str()).c_str(),
                                 MbsToWcsEx(reg_info._val_name.c_str()).c_str(), 
                                 data))
        {
            //log_info "%s", data.c_str() log_end;
            
            if (std::wstring::npos != data.find(MbsToWcsEx(reg_info._val_data.c_str())))
            {
                return true;    // ok, we got!
            }
        }

        return false;
    }
} *PBCReg;