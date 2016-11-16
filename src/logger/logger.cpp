#ifndef UNIT_TEST
#include "logger.h"
#include "Arduino.h"
#include "LoggerFactory.h"
#include <map>

Logger::Logger(const Stream& stream, 
        const ITimeProvider& timeProvider) : 
        timeProvider(timeProvider),
        stream(const_cast<Stream&>(stream)) {   
}

void Logger::setLevel(LogLevel level) {
    this->level = level;
}


void Logger::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    this->log(DEBUG, std::string(format), args);
    va_end(args);
}


void Logger::debug(std::string format, ...) {
    va_list args;
    va_start(args, format);
    this->log(DEBUG, format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(INFO, std::string(format), args);
    va_end(args);
}

void Logger::info(std::string format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(INFO, format, args);
    va_end(args);
}

void Logger::error(const char* format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(ERROR, std::string(format), args);
    va_end(args);
}

void Logger::error(std::string format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(ERROR, format, args);
    va_end(args);
}

void Logger::log(LogLevel level, std::string format, va_list args) {
    if (level < this->level)
        return;
    
    std::string time = timeProvider.now();
    time = time.substr(0, time.size() - 1);
    std::string newFormat = "[%s] " + levelToStr(level) + " " + format + "\n";
    stream.printf(newFormat.c_str(), time.c_str(), args);
}

std::string Logger::levelToStr(LogLevel level) const {
    std::map< LogLevel, std::string > map = {
        { DEBUG, "DEBUG" },
        { INFO, "INFO" },
        { WARN, "WARN" },
        { ERROR, "ERROR" }
    };
    
    return map[level];
}

Logger* Logger::getDefaultLogger() {
    
    if (defaultLogger == 0) {
        defaultLogger = LoggerFactory::createDefaultLogger();
    }
    
    return defaultLogger;
}

Logger* Logger::defaultLogger = 0;

#endif