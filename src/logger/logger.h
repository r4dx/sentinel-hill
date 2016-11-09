#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include "time/TimeString.h"
#include <Stream.h>

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    Logger(const Stream& stream, const ITimeProvider& timeProvider);
    void setLevel(LogLevel level);
    
    void debug(const char* format, ...);
    void debug(std::string format, ...);    
    void info(const char* format, ...);
    void info(std::string format, ...);
    
    static Logger* getDefaultLogger();    
private:
    LogLevel level = DEBUG;
    const ITimeProvider& timeProvider;
    Stream& stream;
    
    void log(LogLevel level, std::string format, va_list args);
    std::string levelToStr(LogLevel level) const;
    
    static Logger* defaultLogger;
};


#endif