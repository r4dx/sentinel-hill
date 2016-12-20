#ifndef UNIT_TEST
#include "logger.h"
#include "Arduino.h"
#include "LoggerFactory.h"
#include <map>

namespace sentinel {
    namespace log {

        Logger::Logger(const Stream& stream, 
                const ITimeProvider& timeProvider) : 
                timeProvider(timeProvider),
                stream(const_cast<Stream&>(stream)) {   
        }

        void Logger::setLevel(LogLevel level) {
            this->level = level;
        }

        const char* Logger::format(LogLevel level, std::string value) {
            std::string time = timeProvider.now();
            time = time.substr(0, time.size() - 1);
            std::string newFormat = "[" + time + "] " + 
                    levelToStr(level) + " " + value + "\n";

            return newFormat.c_str();
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


        void Logger::debug(const char* value) {
            this->log(DEBUG, std::string(value));
        }

        void Logger::debug(std::string value) {
            this->log(DEBUG, value);

        }
        void Logger::info(const char* value) {
            this->log(INFO, std::string(value));
        }

        void Logger::info(std::string value) {
            this->log(INFO, value);
        }

        void Logger::error(const char* value) {
            this->log(ERROR, std::string(value));
        }

        void Logger::error(std::string value) {
            this->log(ERROR, value);
        }

        void Logger::log(LogLevel level, std::string value) {
            if (level < this->level)
                return;

            stream.printf(this->format(level, value));
        }
    }
}
#endif