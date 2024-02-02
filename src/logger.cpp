#include "logger.hpp"

//TO DO: Remove after changing log destination
#include <iostream>

bool Logger::Initialize()
{
    return true;
}

void Logger::Shutdown()
{

}

void Logger::Log(LogLevel level, char* message)
{
    std::string OutMessage = LogLevels[level];
    OutMessage += ": ";
    OutMessage += message;
    OutMessage += "\n";

    std::cout << OutMessage;
}