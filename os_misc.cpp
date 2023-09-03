#include "os_misc.h"

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