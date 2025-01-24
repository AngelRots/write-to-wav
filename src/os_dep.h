#ifndef OS_DEP_H
#define OS_DEP_H

#ifdef _WIN32
#include <windows.h>
#else 
#include <unistd.h>
#endif

typedef char SBYTE;


// I HATE WINDOWS I HATE WINDOWS

void slp(int value)
{
    #ifdef _WIN32
    Sleep(value*1000);
    #else
    sleep(value);
    #endif
}

#endif /* os_dep_h */