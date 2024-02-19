#include "logger.h"

//temp for console logging
#include<cstdio>

bool Logger::Initialize()
{
    return true;
}

void Logger::Shutdown()
{

}

void Logger::Log(LogLevel level, const char* message)
{
    printf("%s: %s\n", LogLevels[level], message);
}