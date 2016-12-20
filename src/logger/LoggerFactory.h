#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H
#include "logger.h"
#include <SD.h>

namespace sentinel {
    namespace log {

        class LoggerFactory {
        public:
            static Logger* createDefaultLogger();

            const static std::string DefaultLoggerFileName;
        private:  
            static File file;
        };
    }
}

#endif /* LOGGERFACTORY_H */

