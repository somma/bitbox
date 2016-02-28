
#include "stdafx.h"
#include "log.h"

int main()
{
    log_dbg "hello, %s", "world" log_end
    log_info "hello, %s", "world" log_end
    log_err "hello, %s", "world" log_end
    return 0;
}

