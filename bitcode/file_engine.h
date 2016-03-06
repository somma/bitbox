/**
 * @file    file_engine.h
 * @brief   
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.03.06 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once
#include "conf.h"

typedef class BCFile
{
public:
    BCFile()
    {
    
    }
    virtual ~BCFile()
    {
    
    }

    /// @brief
    bool is_file_exists(_In_ const char* file_path)
    {
        _ASSERTE(NULL != file_path);
        if (NULL == file_path) return false;

        WIN32_FILE_ATTRIBUTE_DATA info = { 0 };

        //
        // CreateFile()이 아닌 GetFileAttributesEx()를 이용하면 파일이 다른 process에 의해 lock되어 있어도
        // 파일 존재여부를 정확히 체크할 수 있다.
        //
        if (GetFileAttributesExA(file_path, GetFileExInfoStandard, &info) == 0)
            return false;
        else
            return true;
    }

private:


} *PBCFile;

