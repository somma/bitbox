/**
 * @file    file_engine.h
 * @brief   
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.03.06 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once
#include "conf.h"

typedef class BCFile : public IBCEngine
{
public:
    BCFile()
    {
    
    }
    virtual ~BCFile()
    {
    
    }

	bool initialize() { return true; }
	void finalize() { return; }
	BC_ENGINE_TYPE get_engine_type() { return FILE_ENGINE; }

    /// @brief
	bool is_exists(const char* values, ...)
    {
        _ASSERTE(NULL != values);
        if (NULL == values) return false;

        WIN32_FILE_ATTRIBUTE_DATA info = { 0 };

        //
        // CreateFile()이 아닌 GetFileAttributesEx()를 이용하면 파일이 다른 process에 의해 lock되어 있어도
        // 파일 존재여부를 정확히 체크할 수 있다.
        //
        if (GetFileAttributesExA(values, GetFileExInfoStandard, &info) == 0)
            return false;
        else
            return true;
    }

	void dump(const char* values)
	{
		log_info "[Detected File] = %s", values log_end;
	}

private:


} *PBCFile;

