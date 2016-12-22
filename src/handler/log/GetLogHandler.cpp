#include "GetLogHandler.h"
#include <SPI.h>
#include "time/TimeString.h"
#include <logger/ConsoleFileLoggerWrapper.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"

namespace sentinel {
    namespace handler {
        namespace log {
            std::string GetLogHandler::path() const {   
                return "/logs";
            }

            web::Method GetLogHandler::method() const {   
                return web::Method::GET;
            }

            GetLogHandler::GetLogHandler(sentinel::log::Logger* logger) : 
                    logger(logger), 
                    sender(nullptr) {

            }

            void GetLogHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            void GetLogHandler::process() {
                logger->debug("Opening file... " + 
                    sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName);   
                File file = SD.open(
                        sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName.c_str(), 
                            FILE_READ);

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
    }
}