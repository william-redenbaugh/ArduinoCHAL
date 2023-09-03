#ifndef _OS_MISC_H
#define _OS_MISC_H
#include "Arduino.h"
#define os_printf(e...) Serial.printf(e)
#define println(e...) Serial.println(e)

/**
 * @brief Assertion definition implemented for arduino
 */
void OS_ASSERT(bool val);

#endif