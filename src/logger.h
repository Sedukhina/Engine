#ifndef logger
#define logger

#define ENABLE_LOG_WARNING 1
#define ENABLE_LOG_INFO 1
#define ENABLE_LOG_DEBUG 1

enum LogLevel
{
    FATAL = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4
};

const char LogLevels[][10] = {"FATAL", "ERROR", "WARNING", "INFO", "DEBUG"};

class Logger
{
public:
    static bool Initialize();
    static void Shutdown();
    static void Log(LogLevel level, const char* message);
};

#define LOG_FATAL(message) Logger::Log(FATAL, message)
#define LOG_ERROR(message) Logger::Log(ERROR, message)

#if ENABLE_LOG_WARNING == 1
    #define LOG_WARNING(message) Logger::Log(WARNING, message)
#else
    #define LOG_WARNING(message) 
#endif

#if ENABLE_LOG_INFO == 1
    #define LOG_INFO(message) Logger::Log(INFO, message)
#else
    #define LOG_INFO(message) 
#endif

#if ENABLE_LOG_DEBUG == 1
#define LOG_DEBUG(message) Logger::Log(DEBUG, message)
#else
#define LOG_DEBUG(message)
#endif

#endif