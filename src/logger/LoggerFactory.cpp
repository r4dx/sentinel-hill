#include "LoggerFactory.h"
#include <SPI.h>
#include "stream/TwoStreams.h"
#include "sd/File.h"

namespace sentinel {
    namespace log {
        Logger* LoggerFactory::createDefaultLogger() {
            Serial.begin(112500);    
            if (!SD.begin(SS)) {
                Serial.println("ERROR! Could not start SD");
                return new Logger(Serial, *(new MillisTimeProvider()));
            }

            LoggerFactory::file = SD.open(
                    LoggerFactory::DefaultLoggerFileName.c_str(), FILE_WRITE);
            if (!sd::file::valid(&LoggerFactory::file)) {
                Serial.println("ERROR! Could not open file");
                return new Logger(Serial, *(new MillisTimeProvider()));
            }

            return new Logger(*(new TwoStreams(Serial, LoggerFactory::file)), 
                    *(new MillisTimeProvider()));
        }

        File LoggerFactory::file;
        const std::string LoggerFactory::DefaultLoggerFileName = "sh.log";
    }
}