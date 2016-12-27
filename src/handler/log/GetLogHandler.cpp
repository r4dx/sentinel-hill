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
            void GetLogHandler::setPath(web::Method method, std::string uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool GetLogHandler::canHandle() const {   
                return uri.compare("/logs") == 0 && method == web::Method::GET;
            }

            GetLogHandler::GetLogHandler(sentinel::log::Logger* logger) : 
                    logger(logger), 
                    sender(nullptr),
                    uri(""),
                    method(web::Method::DELETE)                    
            {

            }

            void GetLogHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            bool GetLogHandler::handle() {
                logger->debug("Opening file... " + 
                    sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName);   
                File file = SD.open(
                        sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName.c_str(), 
                            FILE_READ);

                if (!sd::file::valid(&file)) {
                    logger->error("Cannot open file");   
                    return false;
                }
                logger->debug("Converting to IWebFile... %s", file.name());
                sd::file::SDWebFile webFile(&file);
                sender->streamFile(webFile, "");
                file.close();
                return true;
            }
        }
    }
}