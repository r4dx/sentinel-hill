#ifndef UNIT_TEST
#include "logger.h"
#include "Arduino.h"
#include <map>

SerialLogger::SerialLogger(unsigned long baud, 
        const ITimeProvider& timeProvider) : timeProvider(timeProvider) {
    Serial.begin(baud);
}

void SerialLogger::setLevel(LogLevel level) {
    this->level = level;
}


void SerialLogger::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    this->log(DEBUG, std::string(format), args);
    va_end(args);
}


void SerialLogger::debug(std::string format, ...) {
    va_list args;
    va_start(args, format);
    this->log(DEBUG, format, args);
    va_end(args);
}

void SerialLogger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(INFO, std::string(format), args);
    va_end(args);
}

void SerialLogger::info(std::string format, ...) {
    va_list args;
    va_start(args, format);  
    this->log(INFO, format, args);
    va_end(args);
}

void SerialLogger::log(LogLevel level, std::string format, va_list args) {
    if (level < this->level)
        return;
    
    std::string time = timeProvider.now();
    time = time.substr(0, time.size() - 1);
    std::string newFormat = "[%s] " + levelToStr(level) + " " + format + "\n";
    Serial.printf(newFormat.c_str(), time.c_str(), args);
}

std::string SerialLogger::levelToStr(LogLevel level) const {
    std::map< LogLevel, std::string > map = {
        { DEBUG, "DEBUG" },
        { INFO, "INFO" },
        { WARN, "WARN" },
        { ERROR, "ERROR" }
    };
    
    return map[level];
}

Logger* Logger::defaultLogger = new SerialLogger(112500, 
        *(new MillisTimeProvider()));

#endif