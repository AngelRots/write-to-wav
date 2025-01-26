#include "xclock.h"

/**
 * @brief OS-Agnostic Sleep function with shitty macros.
 * 
 * @param value The number of seconds for which the calling thread has to sleep.
 */
void xsleep(int value)
{
    #ifdef _WIN32
    Sleep(value*1000);
    #else
    sleep(value);
    #endif
}