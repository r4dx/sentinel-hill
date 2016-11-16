#include "TestHandler.h"
#include <SPI.h>
#include "time/TimeString.h"
#include <logger/LoggerFactory.h>
#include "sd/File.h"

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
    if (!sd::file::valid(&file)) {
        logger->error("Cannot open file");   
        return "";
    }
    logger->debug("Reading file... %s", file.name());
    std::string fileContent = readFromFile(&file);
    logger->debug("Result is " + fileContent);
    std::string result = std::string(fileContent.c_str());
    file.close();
    return result;
}

std::string TestHandler::readFromFile(File* file) {
    std::string result;
    const unsigned int BUFFER_SIZE = 512;
    logger->debug("Starting read...");
    char buffer[BUFFER_SIZE];
    do {
        logger->debug("Delay...");
        // Hack to make sure watchdog is not barking
        delay(0);
        logger->debug("Reading %3u bytes...", BUFFER_SIZE);
        int16_t read = file->read((void*)&buffer, BUFFER_SIZE);
        logger->debug("Read %3u bytes...", read);
        
        if (read <= 0)
            break;
        
        logger->debug("Making string");
        buffer[read - 1] = 0;
        logger->debug("Adding to result");
        result += buffer;
    } while (true);
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
