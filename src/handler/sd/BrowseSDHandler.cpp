#include "BrowseSDHandler.h"
#include <SPI.h>
#include <SD.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"
#include "web/renderer/Body.h"
#include "web/renderer/Text.h"
#include "web/renderer/Link.h"
#include "web/renderer/AsyncHtmlRenderer.h"

namespace sentinel {
    namespace handler {
        namespace sd {
            
            const std::string pathPrefix("/sd");
            
            void BrowseSDHandler::setPath(web::Method method, std::string uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool BrowseSDHandler::canHandle() const {
                return uri.compare(0, pathPrefix.size(), pathPrefix) == 0 && 
                        method == web::Method::GET;
            }
            
            

            std::string BrowseSDHandler::getBrowsePath() {
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
                std::string browsePathS = getBrowsePath();
                const char* browsePath = browsePathS.c_str();
                logger->debug("Browsing SD: %s", browsePath);
                
                if (::sd::file::isFolder(browsePath))
                    return serveFolder(browsePath);
                
                return serveFile(browsePath);
            }
            
            bool BrowseSDHandler::serveFile(const char* browsePath) {
                File file = SD.open(browsePath, FILE_READ);

                if (!::sd::file::valid(&file)) {
                    logger->error("Cannot open file");   
                    return false;
                }
                
                logger->debug("Converting to IWebFile... %s", file.name());
                ::sd::file::SDWebFile webFile(&file);
                sender->streamFile(webFile, "");
                file.close();
                return true;                
            }
            
            bool BrowseSDHandler::serveFolder(const char* browsePath) {
                    File folder = SD.open(browsePath);
                    web::renderer::Body body;
                    web::renderer::AsyncHtmlRenderer renderer(sender);
                    renderer.render(body);
                    
                    for (::sd::file::FileListIterator itr(folder);
                            itr != itr.end(); ++itr) {
                                                
                        std::string linkPath = pathPrefix + "/" + *itr->fileName;
                        web::renderer::Link link(*itr->fileName, linkPath);
                        body.add(link);
                        
                        logger->debug("'%s' in folder '%s' is %s", 
                                itr->fileName->c_str(), browsePath, 
                                itr->isDirectory ? "directory" : "file");
                    }
                    folder.close();
                    return true;                
            }            
        }
    }
}