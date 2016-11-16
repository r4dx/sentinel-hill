#include "LoggerFactory.h"
#include <SPI.h>
#include "stream/TwoStreams.h"

Logger* LoggerFactory::createDefaultLogger() {
    Serial.begin(112500);    
    SD.begin(SS);
    LoggerFactory::file = SD.open(LoggerFactory::DefaultLoggerFileName.c_str(), 
            FILE_WRITE);
    
    return new Logger(*(new TwoStreams(Serial, LoggerFactory::file)), 
            *(new MillisTimeProvider()));
}

File LoggerFactory::file;
const std::string LoggerFactory::DefaultLoggerFileName = "/sentinel-hill.log";