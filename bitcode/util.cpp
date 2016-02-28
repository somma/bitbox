#include "stdafx.h"
#include "log.h"
#include "util.h"

/// @brief
void write_to_console(_In_ uint32_t color, _In_z_ const char* log_message)
{
    _ASSERTE(NULL != log_message);
    if (NULL == log_message) return;

    static HANDLE	con_stdout_handle = INVALID_HANDLE_VALUE;
    static WORD		con_old_color = 0;

    if (INVALID_HANDLE_VALUE == con_stdout_handle)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        con_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(con_stdout_handle, &csbi);
        con_old_color = csbi.wAttributes;
    }

    DWORD len;
    switch (color)
    {
    case wtc_red:
        SetConsoleTextAttribute(con_stdout_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        WriteConsoleA(con_stdout_handle, log_message, (DWORD)strlen(log_message), &len, NULL);
        SetConsoleTextAttribute(con_stdout_handle, con_old_color);
        break;
    case wtc_green:
        SetConsoleTextAttribute(con_stdout_handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        WriteConsoleA(con_stdout_handle, log_message, (DWORD)strlen(log_message), &len, NULL);
        SetConsoleTextAttribute(con_stdout_handle, con_old_color);
        break;
    case wtc_none:
    default:
        WriteConsoleA(con_stdout_handle, log_message, (DWORD)strlen(log_message), &len, NULL);
    }
}


/// @brief  현재 실행중인 프로세스의 파일 명을 리턴한다.
std::wstring get_current_module_fileEx()
{
    std::wstring out;
    if (true != get_current_module_file(out))
    {
        return _null_stringw;
    }
    else
    {
        return out;
    }
}

/// @brief 
bool get_module_path(_In_ const wchar_t* module_name, _Out_ std::wstring& module_path)
{
    DWORD  ret = 0;
    DWORD  buf_len = MAX_PATH;
    LPTSTR buf = (LPTSTR)malloc(buf_len * sizeof(TCHAR));
    if (NULL == buf) return false;

    for (;;)
    {
        ret = GetModuleFileName(GetModuleHandle(module_name), buf, buf_len);
        if (ret == buf_len)
        {
            // buf 가 작은 경우 buf_len 만큼 버퍼가 잘리고, buf_len 리턴 (에러로 간주)
            // 버퍼 사이즈를 2배 늘려서 재 시도
            free(buf);

            buf_len *= 2;
            buf = (LPTSTR)malloc(buf_len * sizeof(TCHAR));
            if (NULL == buf) return false;
        }
        else
        {
            module_path = buf;
            free(buf);
            return true;
        }
    }

    //return false;	// never reach here!
}

/// @brief
bool get_current_module_path(_Out_ std::wstring& module_path)
{
    return get_module_path(NULL, module_path);
}

/// @brief
std::wstring get_current_module_pathEx()
{
    std::wstring out;
    if (true != get_current_module_path(out))
    {
        return _null_stringw;
    }
    else
    {
        return out;
    }
}

/// @brief  
bool get_current_module_file(_Out_ std::wstring& module_file)
{
    std::wstring module_path;
    if (true != get_current_module_path(module_path))
    {
        log_err "get_current_module_path()" log_end
        return false;
    }

    if (true != extract_last_tokenW(module_path, L"\\", module_file, false, false))
    {
        log_err "extract_last_tokenW( org=%s )", module_path.c_str() log_end
            module_file = L"";
        return false;
    }

    return true;
}

/**
 * \brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 앞에서부터 token 을 검색)

			ABCDEFG.HIJ.KLMN	: org_string
				   .			: token
			ABCDEFG             : out_string if forward = TRUE
					HIJ.KLMN	: out_string if forward = FALSE

			delete_token 가 True 인 경우 org_string 에서 out_string + token 을 삭제

 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
bool
extract_first_tokenW(
	_In_ std::wstring& org_string,
	_In_ const std::wstring& token,
	_Out_ std::wstring& out_string, 
	_In_ bool forward,
	_In_ bool delete_token
	)
{
    if (true == delete_token)
    {
        if (&org_string == &out_string) 
        {
#ifndef TEST_EXPORTS
            _ASSERTE(!"prarameters conflict! ");
#endif
            return false;
        }
    }

	size_t pos = org_string.find(token);
	if (std::wstring::npos == pos)
	{
        out_string = org_string;
        return true;
	}

	if (true== forward)
	{
		out_string = org_string.substr(0, pos);
        if (delete_token) org_string.erase(0, pos + token.size());
	}
	else
	{
		out_string = org_string.substr(pos + token.size(), org_string.size());
        if (delete_token) org_string.erase(pos, org_string.size());
	}
    return true;
}

/**
 * \brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 앞에서부터 token 을 검색)

			ABCDEFG.HIJ.KLMN	: org_string
				   .			: token
			ABCDEFG             : out_string if forward = TRUE
					HIJ.KLMN	: out_string if forward = FALSE
 * @param	
 * @see		
 * @remarks 성공 시 분리된 문자열을 스트링 객체에 리턴
			실패 시 _nullstringw 리턴
 * @code		
 * @endcode	
 * @return	
**/
std::wstring 
extract_first_tokenExW(
	_In_ const wchar_t* org,
	_In_ const wchar_t* token,	
	_In_ bool forward
	)
{
	_ASSERTE(NULL != org);
	_ASSERTE(NULL != token);
	if (NULL == org || NULL == token) return _null_stringw;

	std::wstring org_string = org;
	std::wstring out_string;
	if (true != extract_first_tokenW(org_string, token, out_string, forward, false)) 
		return _null_stringw;
	else
		return out_string;
}


/**
 * @brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 앞에서부터 token 을 검색)
			
			ABCDEFG.HIJ.KLMN	: org_string
			       .			: token
		    ABCDEFG             : out_string if forward = TRUE
			        HIJ.KLMN	: out_string if forward = FALSE

            delete_token 가 True 인 경우 org_string 에서 out_string + token 을 삭제
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
bool
extract_first_tokenA(
	_In_ std::string& org_string,
	_In_ const std::string& token,
	_Out_ std::string& out_string, 
	_In_ bool forward,
	_In_ bool delete_token
    )	
{
    if (true == delete_token)
    {
        if (&org_string == &out_string) 
        {
#ifndef TEST_EXPORTS
            _ASSERTE(!"prarameters conflict! ");
#endif
            return false;;
        }
    }

	size_t pos = org_string.find(token);
	if (std::string::npos == pos)
	{
        out_string = org_string;
        return true;
	}

	if (TRUE == forward)
	{
		out_string = org_string.substr(0, pos);
        if (delete_token) org_string.erase(0, pos + token.size());
	}
	else
	{
		out_string = org_string.substr(pos + token.size(), org_string.size());
        if (delete_token) org_string.erase(pos, org_string.size());
	}
    return true;
}

/**
 * @brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 앞에서부터 token 을 검색)
			
			ABCDEFG.HIJ.KLMN	: org_string
			       .			: token
		    ABCDEFG             : out_string if forward = TRUE
			        HIJ.KLMN	: out_string if forward = FALSE

 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
std::string
extract_first_tokenExA(
		_In_ const char* org,
		_In_ const char* token,		
		_In_ bool forward
		)
{
	_ASSERTE(NULL != org);
	_ASSERTE(NULL != token);
	if (NULL == org || NULL == token) return _null_stringa;

	std::string org_string = org;
	std::string out_string;
	if (true != extract_first_tokenA(org_string, token, out_string, forward, false)) 
		return _null_stringa;
	else
		return out_string;
}

/**
 * @brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 뒤에서부터 token 을 검색)

			ABCDEFG.HIJ.KLMN	: org_string
					   .		: token
			ABCDEFG.HIJ			: out_string if forward = TRUE
					    KLMN	: out_string if forward = FALSE

			delete_token 가 True 인 경우 org_string 에서 out_string + token 을 삭제
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
bool 
extract_last_tokenW(
	_In_ std::wstring& org_string,
	_In_ const std::wstring& token,
	_Out_ std::wstring& out_string, 
	_In_ bool forward,
	_In_ bool delete_token
	)
{
    if (true== delete_token)
    {
        if (&org_string == &out_string) 
        {
#ifndef TEST_EXPORTS
            _ASSERTE(!"prarameters conflict! ");
#endif
            return false;
        }
    }

    size_t pos = org_string.rfind(token);
	if (std::wstring::npos == pos)
	{
        out_string = org_string;
        return true;
	}

	if (true== forward)
	{
		out_string = org_string.substr(0, pos);
        if (delete_token) org_string.erase(0, pos + token.size());
	}
	else
	{
        out_string = org_string.substr(pos + token.size(), org_string.size());
        if (delete_token) org_string.erase(pos, org_string.size());
	}
    return true;
}

/**
 * @brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 뒤에서부터 token 을 검색)

			ABCDEFG.HIJ.KLMN	: org_string
					   .		: token
			ABCDEFG.HIJ			: out_string if forward = TRUE
					    KLMN	: out_string if forward = FALSE
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
std::wstring
extract_last_tokenExW(
	_In_ const wchar_t* org,
	_In_ const wchar_t* token,	
	_In_ bool forward
	)
{
	_ASSERTE(NULL != org);
	_ASSERTE(NULL != token);
	if (NULL == org || NULL == token) return _null_stringw;

	std::wstring org_string = org;
	std::wstring out_string;
	if (true != extract_last_tokenW(org_string, token, out_string, forward, false))
		return _null_stringw;
	else
		return out_string;
}

/**
 * @brief	org_string 에서 token 을 검색해서 문자열을 잘라낸다. 
			(org_string 의 뒤에서부터 token 을 검색)
			
			ABCDEFG.HIJ.KLMN	: org_string
			           .		: token
		    ABCDEFG.HIJ			: out_string if forward = TRUE
						KLMN	: out_string if forward = FALSE

            delete_token 가 True 인 경우 org_string 에서 out_string + token 을 삭제
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
bool 
extract_last_tokenA(
	_In_ std::string& org_string,
	_In_ const std::string& token,
	_Out_ std::string& out_string, 
	_In_ bool forward,
	_In_ bool delete_token
    )
{
    if (TRUE == delete_token)
    {
        if (&org_string == &out_string) 
        {
#ifndef TEST_EXPORTS
            _ASSERTE(!"prarameters conflict! ");
#endif
            return false;
        }
    }

	size_t pos = org_string.rfind(token);
	if (std::string::npos == pos)
	{
        out_string = org_string;
        return true;
	}

	if (true == forward)
	{
		out_string = org_string.substr(0, pos);
        if (delete_token) org_string.erase(0, pos + token.size());
	}
	else
	{
        out_string = org_string.substr(pos + token.size(), org_string.size());
        if (delete_token) org_string.erase(pos, org_string.size());
	}
    return true;
}

/**
 * @brief	
 * @param	
 * @see		
 * @remarks	
 * @code		
 * @endcode	
 * @return	
**/
std::string
extract_last_tokenExA(
	_In_ const char* org,
	_In_ const char* token,
	_In_ bool forward
    )
{
	_ASSERTE(NULL != org);
	_ASSERTE(NULL != token);
	if (NULL == org || NULL == token) return _null_stringa;

	std::string org_string = org;
	std::string out_string;
	if (true != extract_last_tokenA(org_string, token, out_string, forward, false))
		return _null_stringa;
	else
		return out_string;

}



/**
* @brief	trim 함수들

            string szbuf="__12345_____";  
            cout<<"Before trim: "<<szbuf<<endl;  
            cout<<"After  trim: "<<trim(szbuf,"_")<<endl;
            cout<<"After rtrim: "<<rtrim(szbuf,"_")<<endl;
            cout<<"After ltrim: "<<ltrim(szbuf,"_")<<endl;
            ----------------------------------------------
            Before trim: __12345_____
            After  trim: 12345
            After rtrim: __12345
            After ltrim: 12345
* @param	
* @see		
* @remarks	
* @code		
* @endcode	
* @return	
*/
std::string trima(std::string& s, const std::string& drop)
{
    std::string r=s.erase(s.find_last_not_of(drop)+1);
    return r.erase(0,r.find_first_not_of(drop));
}
std::string rtrima(std::string& s, const std::string& drop)
{
  return s.erase(s.find_last_not_of(drop)+1); 
}
std::string ltrima(std::string& s, const std::string& drop)
{ 
  return s.erase(0,s.find_first_not_of(drop)); 
}
std::wstring  trimw(std::wstring& s, const std::wstring& drop)
{
    std::wstring r=s.erase(s.find_last_not_of(drop)+1);
    return r.erase(0,r.find_first_not_of(drop));
}
std::wstring rtrimw(std::wstring& s, const std::wstring& drop)
{
    return s.erase(s.find_last_not_of(drop)+1); 
}
std::wstring ltrimw(std::wstring& s, const std::wstring& drop)
{
    return s.erase(0,s.find_first_not_of(drop)); 
}


