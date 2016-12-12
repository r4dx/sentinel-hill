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
    
    template <typename ... Args>
    inline void debug(const char* format, Args const & ... args) {
        this->log(DEBUG, std::string(format), args ...);
    }

    template <typename ... Args>
    inline void debug(std::string format, Args const & ... args) {
        this->log(DEBUG, format, args ...);

    }
    template <typename ... Args>
    inline void info(const char* format, Args const & ... args) {
        this->log(INFO, std::string(format), args ...);
    }

    template <typename ... Args>
    inline void info(std::string format, Args const & ... args) {
        this->log(INFO, format, args ...);
    }

    template <typename ... Args>
    inline void error(const char* format, Args const & ... args) {
        this->log(ERROR, std::string(format), args ...);
    }

    template <typename ... Args>
    inline void error(std::string format, Args const & ... args) {
        this->log(ERROR, format, args ...);
    }
    
    
    void debug(const char* value);
    void debug(std::string value);    
    void info(const char* value);
    void info(std::string value);
    void error(const char* value);   
    void error(std::string value);    
    
    
    static Logger* getDefaultLogger();    
private:
    LogLevel level = DEBUG;
    const ITimeProvider& timeProvider;
    Stream& stream;
    
    void log(LogLevel level, std::string value);
    const char* format(LogLevel level, std::string value);
    std::string levelToStr(LogLevel level) const;    
    
    static Logger* defaultLogger;
    
    template <typename ... Args>
    void log(LogLevel level, std::string format, Args const & ... args) {
        if (level < this->level)
            return;

        const char* newFormat = this->format(level, format);

        stream.printf(newFormat, args ...);
    }
};


#endif