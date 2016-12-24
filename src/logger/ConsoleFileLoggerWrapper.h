#ifndef CONSOLEFILELOGGERWRAPPER_H
#define CONSOLEFILELOGGERWRAPPER_H
#include "logger.h"
#include <SD.h>
#include <string>
#include <stream/DualStreamValve.h>
#include "time/TimeString.h"

namespace sentinel {
    namespace log {
        class ConsoleFileLoggerWrapper {
        public:
            ConsoleFileLoggerWrapper(std::string fileName, 
                    ITimeProvider& timeProvider);
            
            virtual ~ConsoleFileLoggerWrapper();
            Logger* get();
            bool erase();
            
            const static std::string DefaultLoggerFileName;
        private:  
            File file;
            std::string fileName;
            ITimeProvider& timeProvider;
            
            Logger* logger;
            stream::DualStreamValve* dualStream;
            
            bool openFile();
        };
    }
}

#endif /* CONSOLEFILELOGGERWRAPPER_H */

