#ifndef MOTORHANDLER_H
#define MOTORHANDLER_H

#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <string>
#include <memory>

namespace sentinel {
    namespace handler {
        namespace motor {
            class MotorHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, 
                    std::shared_ptr<std::string> uri) override;
                
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                MotorHandler(sentinel::log::Logger& logger);
            private:
                std::shared_ptr<std::string> uri;
                web::Method method;                
                
                web::IWebSender* sender;
                sentinel::log::Logger& logger;
            };
        }
    }
}
#endif /* MOTORHANDLER_H */

