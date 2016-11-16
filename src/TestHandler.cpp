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
    logger->debug("Opening file... " + LoggerFactory::DefaultLoggerFileName);   
    File file = SD.open(LoggerFactory::DefaultLoggerFileName.c_str(), FILE_READ);
    if (strlen(file.name()) == 0) {
        logger->error("Cannot open file");   
        return "";
    }
    logger->debug("Reading file... %s", file.name());   
    String fileContent = file.readString();
    logger->debug("Result is " + std::string(fileContent.c_str()));
    std::string result = std::string(fileContent.c_str());
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
    if (logs == "")
        return WebResponse::invalid;
    
    return WebResponse(logs);
}
