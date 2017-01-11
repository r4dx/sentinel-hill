#include "BrowseSDHandler.h"
#include <SPI.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"

namespace sentinel {
    namespace handler {
        namespace sd {
            void BrowseSDHandler::setPath(web::Method method, std::string uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool BrowseSDHandler::canHandle() const {
                std::string prefix("/sd");
                return uri.compare(0, prefix.size(), prefix) == 0 && 
                        method == web::Method::GET;
            }

            BrowseSDHandler::BrowseSDHandler(sentinel::log::Logger* logger) : 
                    logger(logger), 
                    sender(nullptr),
                    uri(""),
                    method(web::Method::GET) { }

            void BrowseSDHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            bool BrowseSDHandler::handle() {
                logger->debug("Browsing SD");   
                
                return true;
            }
        }
    }
}