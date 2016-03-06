#pragma once

#ifndef _TODO_DEFINED_
#define LINE1(x)	#x
#define LINE(x)		LINE1(x)
#define TODO(msg)	message(  __FILE__"(" LINE(__LINE__) ") [TODO] " msg )
#define todo TODO
#endif

#define free_and_nil(p)     do { if (NULL != p) { free(p); p = NULL;} } while(p != NULL);

#define     _pause  _getch()




wchar_t* MbsToWcs(_In_ const char* mbs);
char* WcsToMbs(_In_ const wchar_t* wcs);
char* WcsToMbsUTF8(_In_ const wchar_t* wcs);
wchar_t* Utf8MbsToWcs(_In_ const char* utf8);

static const std::wstring _null_stringw(L"");
static const std::string  _null_stringa("");


class SafePtr
{
public:
    SafePtr(void* ptr) : _ptr(ptr) {}
    ~SafePtr() { free_and_nil(_ptr); }
    void* get() { return _ptr; };
private:
    void* _ptr;
};
std::wstring MbsToWcsEx(_In_ const char *mbs);
std::string WcsToMbsEx(_In_ const wchar_t *wcs);



#define wtc_none    0
#define wtc_red     1
#define wtc_green   2
void write_to_console(_In_ uint32_t color, _In_z_ const char* log_message);
std::wstring get_current_module_fileEx();
bool get_module_path(_In_ const wchar_t* module_name, _Out_ std::wstring& module_path);
bool get_current_module_path(_Out_ std::wstring& module_path);
std::wstring get_current_module_pathEx();
bool get_current_module_file(_Out_ std::wstring& module_file);
bool
extract_first_tokenW(
    _In_ std::wstring& org_string,
    _In_ const std::wstring& token,
    _Out_ std::wstring& out_string,
    _In_ bool forward,
    _In_ bool delete_token
    );
std::wstring
extract_first_tokenExW(
    _In_ const wchar_t* org,
    _In_ const wchar_t* token,
    _In_ bool forward
    );
bool
extract_first_tokenA(
    _In_ std::string& org_string,
    _In_ const std::string& token,
    _Out_ std::string& out_string,
    _In_ bool forward,
    _In_ bool delete_token
    );
std::string
extract_first_tokenExA(
    _In_ const char* org,
    _In_ const char* token,
    _In_ bool forward
    );
bool
extract_last_tokenW(
    _In_ std::wstring& org_string,
    _In_ const std::wstring& token,
    _Out_ std::wstring& out_string,
    _In_ bool forward,
    _In_ bool delete_token
    );
std::wstring
extract_last_tokenExW(
    _In_ const wchar_t* org,
    _In_ const wchar_t* token,
    _In_ bool forward
    );
bool
extract_last_tokenA(
    _In_ std::string& org_string,
    _In_ const std::string& token,
    _Out_ std::string& out_string,
    _In_ bool forward,
    _In_ bool delete_token
    );
std::string
extract_last_tokenExA(
    _In_ const char* org,
    _In_ const char* token,
    _In_ bool forward
    );
std::string trima(std::string& s, const std::string& drop);
std::string rtrima(std::string& s, const std::string& drop);
std::string ltrima(std::string& s, const std::string& drop);
std::wstring  trimw(std::wstring& s, const std::wstring& drop);
std::wstring rtrimw(std::wstring& s, const std::wstring& drop);
std::wstring ltrimw(std::wstring& s, const std::wstring& drop);


bool set_privilege(_In_z_ const wchar_t* privilege, _In_ bool enable);