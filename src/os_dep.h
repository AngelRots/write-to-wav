#ifndef OS_DEP_H
#define OS_DEP_H

#ifdef _WIN32
#include <windows.h>
#else 
#include <unistd.h>
#endif

typedef char SBYTE;

#define OS_PATHMAX 260
#define PI         3.14159265358979323846
#define MAX_AMP    32767


#endif /* os_dep_h */