#include "global_includes.h"

void os_println_cmd(const char *fmt, ...)
{
    Serial.printf(fmt);
    Serial.printf("\n");
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