/**
 * @file    proc_engine.h
 * @brief   
 * @author  Yonhgwhan, Noh (fixbrain@gmail.com)
 * @date    2016.03.06 14:36 created.
 * @copyright All rights reserved by Yonghwan, Noh.
**/
#pragma once
#include "conf.h"
#include "util.h"
#include "process_tree.h"

typedef class BCProcs : public IBCEngine
{
private:
    cprocess_tree   _proc_tree;
public:
    BCProcs()
    {
    
    }
    virtual ~BCProcs()
    {
    
    }

    /// @brief
	bool initialize()
    {
        // build process tree
        if (true != _proc_tree.build_process_tree())
        {
            log_err "cprocess_tree::build_process_tree() failed." log_end;
            return false;
        }
        
        //_proc_tree.print_process_tree(448);
        return true;
    }

    /// @brief
	void finalize()
    {
        // free process tree
        _proc_tree.clear_process_tree();
    }

	BC_ENGINE_TYPE get_engine_type() { return PROC_ENGINE; }

    /// @brief
	bool is_exists(const char* values, ...)
    {
		_ASSERTE(NULL != values);
		if (NULL == values) return false;

        DWORD pid = _proc_tree.find_process(MbsToWcsEx(values).c_str());
        if (0 != pid)
        {
            return true;
        }
        return false;
    }
} *PBCProcs;