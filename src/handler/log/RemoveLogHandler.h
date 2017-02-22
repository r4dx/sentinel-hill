#ifndef REMOVELOGHANDLER_H
#define REMOVELOGHANDLER_H

#include "web/IWebHandler.h"
#include "logger/ConsoleFileLoggerWrapper.h"
#include <SD.h>
#include <string>
#include <memory>

namespace sentinel {
    namespace handler {
        namespace log {
            class RemoveLogHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, 
                    std::shared_ptr<std::string> uri) override;
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                RemoveLogHandler(sentinel::log::ConsoleFileLoggerWrapper& loggerWrapper);
            private:
                std::shared_ptr<std::string> uri;
                web::Method method;
                
                web::IWebSender* sender;
                sentinel::log::ConsoleFileLoggerWrapper& loggerWrapper;
            };
        }
    }
}
#endif /* REMOVELOGHANDLER_H */

