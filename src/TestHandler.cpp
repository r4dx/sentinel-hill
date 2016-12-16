#include "TestHandler.h"
#include <SPI.h>
#include "time/TimeString.h"
#include <logger/LoggerFactory.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"

namespace sentinel {
    std::string TestHandler::path() const {   
        return "/Test";
    }

    web::Method TestHandler::method() const {   
        return web::Method::GET;
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

    TestHandler::TestHandler(Logger* logger) : logger(logger), sender(nullptr) {

    }
    
    void TestHandler::setSender(web::IWebSender& sender) {
        this->sender = &sender;
    }

    void TestHandler::process() {
        logger->debug("Opening file... " + LoggerFactory::DefaultLoggerFileName);   
        File file = SD.open(LoggerFactory::DefaultLoggerFileName.c_str(), FILE_READ);
        if (!sd::file::valid(&file)) {
            logger->error("Cannot open file");   
            return;
        }
        logger->debug("Converting to IWebFile... %s", file.name());
        sd::file::SDWebFile webFile(&file);
        sender->streamFile(webFile, "");
        file.close();
    }
}