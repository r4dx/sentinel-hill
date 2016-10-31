#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include "time/TimeString.h"

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    virtual void setLevel(LogLevel level) = 0;
    
    virtual void debug(const char* format, ...) = 0;
    virtual void debug(std::string format, ...) = 0;        
    virtual void info(const char* format, ...) = 0;
    virtual void info(std::string format, ...) = 0;    
    
    static Logger* defaultLogger;
};

class SerialLogger : public Logger {
public:
    SerialLogger(unsigned long baud, const ITimeProvider& timeProvider);
    void setLevel(LogLevel level);
    
    void debug(const char* format, ...);
    void debug(std::string format, ...);    
    void info(const char* format, ...);
    void info(std::string format, ...);
    
private:
    LogLevel level = DEBUG;
    const ITimeProvider& timeProvider;
    void log(LogLevel level, std::string format, va_list args);
    std::string levelToStr(LogLevel level) const;
};

#endif