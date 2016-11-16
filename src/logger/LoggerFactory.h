#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H
#include "logger.h"
#include <SD.h>

class LoggerFactory {
public:
    static Logger* createDefaultLogger();
    
    const static std::string DefaultLoggerFileName;
private:  
    static File file;
};


#endif /* LOGGERFACTORY_H */

