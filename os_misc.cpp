#include "global_includes.h"

void os_println_cmd(const char *fmt, ...)
{
    os_printf(fmt);
    os_printf("\n");
}

void OS_ASSERT(bool val)
{
    if (val)
    {
        for (;;)
        {
            int n;
            (void)n;
        }
    }
}