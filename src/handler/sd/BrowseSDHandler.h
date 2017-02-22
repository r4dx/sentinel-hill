#ifndef BROWSESDHANDLER_H
#define BROWSESDHANDLER_H

#include "web/IWebHandler.h"
#include "web/renderer/IRenderer.h"
#include "logger/logger.h"
#include <SD.h>
#include <string>
#include <memory>

namespace sentinel {
    namespace handler {
        namespace sd {
            class BrowseSDHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, 
                    std::shared_ptr<std::string> uri) override;
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                BrowseSDHandler(sentinel::log::Logger& logger);
            private:
                
                const std::string pathPrefix;
                
                std::string browsePath;
                std::shared_ptr<std::string> uri;
                web::Method method;
                
                web::IWebSender* sender;
                sentinel::log::Logger& logger;
                
                std::string getBrowsePath();
                bool serveFile();
                bool serveFolder();
                void renderUpLink(web::renderer::IRenderer* renderer);
            };
        }
    }
}
#endif /* BROWSESDHANDLER_H */

