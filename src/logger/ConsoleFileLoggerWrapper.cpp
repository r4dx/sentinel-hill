#include "ConsoleFileLoggerWrapper.h"
#include <SPI.h>
#include "stream/DualStreamValve.h"
#include "sd/File.h"

namespace sentinel {
    namespace log {
        
        ConsoleFileLoggerWrapper::ConsoleFileLoggerWrapper(std::string fileName, 
                time::ITimeProvider& timeProvider) :

                logger(nullptr),
                dualStream(nullptr),
                fileName(fileName),
                timeProvider(timeProvider)
        {
            
            Serial.begin(112500);
            
            if (!SD.begin(SS)) {
                Serial.println("ERROR! Could not start SD");
                logger = new Logger(Serial, timeProvider);
                return;
            }
            
            if (!openFile()) {
                Serial.println("ERROR! Could not open file");
                logger = new Logger(Serial, timeProvider);
                return;
            }

            dualStream = new stream::DualStreamValve(Serial, file);
            logger = new Logger(*dualStream, timeProvider);
        }
        
        bool ConsoleFileLoggerWrapper::openFile() {
            file = SD.open(fileName.c_str(), FILE_WRITE);
            return sd::file::valid(&file);
        }
        
        ConsoleFileLoggerWrapper::~ConsoleFileLoggerWrapper() {
            delete logger;
            
            if (dualStream != nullptr)
                delete dualStream;
            
            if (sd::file::valid(&file))
                file.close();
        }
        
        Logger& ConsoleFileLoggerWrapper::get() {
            return *logger;
        }
        
        bool ConsoleFileLoggerWrapper::erase() {
            if (dualStream == nullptr)
                return false;
            
            dualStream->off(stream::StreamNum::Second);
            file.close();
            logger->info("Removing file - %s!", fileName.c_str());
            
            // This hacky cast came from here: http://www.esp8266.com/viewtopic.php?f=32&t=10755
            SD.remove((char*)fileName.c_str());
            if (!openFile()) {
                Serial.println("ERROR! Could not open file");
                delete logger;
                delete dualStream;
                logger = new Logger(Serial, timeProvider);
                return false;
            }
            dualStream->substitute(stream::StreamNum::Second, file);
            dualStream->on(stream::StreamNum::Second);
            return true;
        }
        const char ConsoleFileLoggerWrapper::DefaultLoggerFileName[] = "/sh.log";
    }
}