#ifndef _OS_MISC_H
#define _OS_MISC_H
#include "Arduino.h"

void os_println_cmd(const char *fmt, ...);
// Macro: println(e)
// Description: Prints the given expression followed by a newline character.
#define os_println(...) os_println_cmd(__VA_ARGS__)

// Macro: print(e)
// Description: Prints the given expression.
#ifndef print
#define print(...) os_printf(__VA_ARGS__)
#endif
// Macro: os_printf(e)
// Description: Prints the formatted output using the os_printf function.
#define os_printf(...) Serial.printf(__VA_ARGS__)

#define os_println(...) os_printf(__VA_ARGS__); os_printf("\n")
#define os_random(e) random(e)

/**
 * @brief Assertion definition implemented for arduino
 */
void OS_ASSERT(bool val);

#endif