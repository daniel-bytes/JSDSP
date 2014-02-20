#include "Debugging.h"
#include <iostream>

#if WIN32
#include <Windows.h>
#endif


void PrintErrorLine(const char *err)
{
    PrintError(err);
    PrintError("\r\n");
}

void PrintError(const char *err)
{
#if DEBUG
    std::cerr << "Error: " << err << std::endl;
#if WIN32
    OutputDebugString(err);
#endif //WIN32
#endif //DEBUG
}