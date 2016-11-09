#include "TestHandler.h"
#include <SD.h>
#include <SPI.h>
#include "time/TimeString.h"
#include <logger/LoggerFactory.h>

std::string TestHandler::getPath() const {   
    return "Test";
}

void TestHandler::sd_test() {
    logger->info("SD Init start");
    
    if (!SD.begin(SS))
        logger->info("SD Init FAIL");
    
    logger->info("SD Init OK %u", SD.totalClusters());
    File file = SD.open("GOTCHA", FILE_WRITE);
    file.print(MillisTimeProvider().now().c_str());
    file.flush();
    file.close();
    
    file = SD.open("GOTCHA", FILE_READ);
    logger->info(file.readString().c_str());
    file.close();
}

std::string TestHandler::getLogs() {
    File file = SD.open(LoggerFactory::DefaultLoggerFileName.c_str(), FILE_READ);
    std::string result = std::string(file.readString().c_str());
    file.close();
    return result;
}

TestHandler::TestHandler(Logger* logger) : logger(logger) {

}


WebResponse TestHandler::post(WebRequest& request) {
    return WebResponse("<html><h1>POST</h1></html>");
}

WebResponse TestHandler::get(WebRequest& request) {
    std::string logs = getLogs();
    
    return WebResponse(getLogs());
}
