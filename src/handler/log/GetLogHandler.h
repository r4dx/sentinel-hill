#ifndef GETLOGHANDLER_H
#define GETLOGHANDLER_H

#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <SD.h>
#include <string>

namespace sentinel {
    namespace handler {
        namespace log {
            class GetLogHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, std::string uri) override;
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                GetLogHandler(sentinel::log::Logger* logger);
                ~GetLogHandler() override {}
            private:
                std::string uri;
                web::Method method;                
                
                web::IWebSender* sender;
                sentinel::log::Logger* logger;
            };
        }
    }
}
#endif /* GETLOGHANDLER_H */

