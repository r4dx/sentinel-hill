#include "ConsoleFileLoggerWrapper.h"
#include <SPI.h>
#include "stream/DualPrint.h"
#include "sd/File.h"

namespace sentinel {
    namespace log {
        
        ConsoleFileLoggerWrapper::ConsoleFileLoggerWrapper(std::string fileName, 
                ITimeProvider& timeProvider) :

                logger(nullptr),
                dualPrint(nullptr),
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

            dualPrint = new stream::DualPrint(Serial, file);
            logger = new Logger(*dualPrint, timeProvider);
        }
        
        bool ConsoleFileLoggerWrapper::openFile() {
            file = SD.open(fileName.c_str(), FILE_WRITE);
            return !sd::file::valid(&file);
        }
        
        ConsoleFileLoggerWrapper::~ConsoleFileLoggerWrapper() {
            delete logger;
            
            if (dualPrint != nullptr)
                delete dualPrint;
            
            if (sd::file::valid(&file))
                file.close();
        }
        
        Logger* ConsoleFileLoggerWrapper::get() {
            return logger;
        }
        
        bool ConsoleFileLoggerWrapper::erase() {
            if (dualPrint == nullptr)
                return false;
            
            dualPrint->suspend(stream::PrintNum::Second);
            file.close();
            SD.remove(fileName.c_str());
            if (!openFile()) {
                Serial.println("ERROR! Could not open file");
                delete logger;
                delete dualPrint;
                logger = new Logger(Serial, timeProvider);
                return false;
            }
            dualPrint->substitute(stream::PrintNum::Second, file);
            dualPrint->resume(stream::PrintNum::Second);
            return true;
        }
        
        const std::string ConsoleFileLoggerWrapper::DefaultLoggerFileName = "sh.log";
    }
}