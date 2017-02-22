#include "BrowseSDHandler.h"
#include <SPI.h>
#include <SD.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"
#include "web/renderer/Text.h"
#include "web/renderer/Link.h"
#include "web/renderer/AsyncHtmlRenderer.h"

namespace sentinel {
    namespace handler {
        namespace sd {
                        
            void BrowseSDHandler::setPath(web::Method method, 
                    std::shared_ptr<std::string> uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool BrowseSDHandler::canHandle() const {
                return uri->compare(0, pathPrefix.size(), pathPrefix) == 0 && 
                        method == web::Method::GET;
            }
            
            

            std::string BrowseSDHandler::getBrowsePath() {
                return uri->substr(3);
            }            
            
            BrowseSDHandler::BrowseSDHandler(sentinel::log::Logger& logger) : 
                    logger(logger), 
                    sender(nullptr),
                    uri(std::shared_ptr<std::string>()),
                    pathPrefix("/sd"),
                    method(web::Method::GET) { }

            void BrowseSDHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            bool BrowseSDHandler::handle() {
                browsePath = getBrowsePath();
                logger.debug("Browsing SD: %s", browsePath.c_str());
                
                if (sentinel::sd::file::isFolder(browsePath.c_str()))
                    return serveFolder();
                
                return serveFile();
            }
            
            bool BrowseSDHandler::serveFile() {
                File file = SD.open(browsePath.c_str(), FILE_READ);

                if (!sentinel::sd::file::valid(file)) {
                    logger.error("Cannot open file");   
                    return false;
                }
                
                logger.debug("Converting to IWebFile... %s", file.name());
                sentinel::sd::file::SDWebFile webFile(file);
                sender->streamFile(webFile, "");
                file.close();
                return true;                
            }
            
            bool BrowseSDHandler::serveFolder() {
                web::renderer::AsyncHtmlRenderer renderer(sender);
                const std::string BODY_TAG = "body";
                renderer.start(BODY_TAG);
                renderUpLink(&renderer);
                    
                File folder = SD.open(browsePath.c_str());
                for (sentinel::sd::file::FileListIterator itr(folder);
                        itr != itr.end(); ++itr) {
                    
                    std::string linkPath = pathPrefix + browsePath + *itr->fileName;                    
                    if (itr->isDirectory)
                        linkPath += "/";
                    
                    web::renderer::Link link(*itr->fileName, linkPath);
                    renderer.render(link);
                    renderer.newLine();
                    logger.debug("'%s' in folder '%s' is %s", 
                            itr->fileName->c_str(), browsePath.c_str(), 
                            itr->isDirectory ? "directory" : "file");
                }
                folder.close();
                renderer.end(BODY_TAG);
                return true;                
            }
            
            void BrowseSDHandler::renderUpLink(web::renderer::IRenderer* renderer) {
                const std::string delimiter = "/";
                if (browsePath == "" || browsePath == delimiter || 
                        browsePath.size() < 2)
                    return;
                
                std::size_t found = browsePath.find_last_of(delimiter, 
                        browsePath.size() - 2);
                
                if (found == std::string::npos)
                    return;
                
                std::string upPath = pathPrefix + browsePath.substr(0, found) + 
                        delimiter;
                web::renderer::Link link("..", upPath);
                renderer->render(link);
                renderer->newLine();
            }
        }
    }
}