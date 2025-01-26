#ifndef XCLOCK_H
#define XCLOCK_H

#ifdef _WIN32
#include <windows.h>
#else 
#include <unistd.h>
#endif

void xsleep(int value);

#endif /* xclock_h */