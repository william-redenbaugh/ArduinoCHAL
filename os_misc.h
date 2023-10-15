#ifndef _OS_MISC_H
#define _OS_MISC_H
#include "Arduino.h"

void os_println_cmd(const char *fmt, ...);
// Macro: println(e)
// Description: Prints the given expression followed by a newline character.
#define os_println(e, ...) os_println_cmd(e)

// Macro: print(e)
// Description: Prints the given expression.
#define print(e, ...) Serial.printf(e)

// Macro: os_printf(e)
// Description: Prints the formatted output using the Serial.printf function.
#define os_printf(e, ...) Serial.printf(e)

#define os_random(e) random(e)

/**
 * @brief Assertion definition implemented for arduino
 */
void OS_ASSERT(bool val);

#endif