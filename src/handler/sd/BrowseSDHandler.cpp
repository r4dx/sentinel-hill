#include "BrowseSDHandler.h"
#include <SPI.h>
#include <SD.h>
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

            std::string BrowseSDHandler::getBrowseFolder() {
                return uri.substr(3);
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
                std::string folderNameS = getBrowseFolder();
                const char* folderName = folderNameS.c_str();
                logger->debug("Browsing SD folder: %s", folderName);
                if (::sd::file::isFolder(folderName)) {
                    File folder = SD.open(folderName);
                    folder.rewindDirectory();
                    for (::sd::file::FileListIterator itr(folder);
                            itr != itr.end(); ++itr) {
                        logger->debug("'%s' in folder '%s' is %s", 
                                itr->fileName->c_str(), folderName, 
                                itr->isDirectory ? "directory" : "file");
                    }
                    folder.close();
                }
                return true;
            }
        }
    }
}