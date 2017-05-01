#ifndef MOTORHANDLER_H
#define MOTORHANDLER_H

#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <string>
#include <memory>
#include <stdint.h>
#include "Adafruit_MCP23017.h"

namespace sentinel {
    namespace handler {
        namespace motor {
            class IOExpanderHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, 
                    std::shared_ptr<std::string> uri) override;
                
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                IOExpanderHandler(sentinel::log::Logger& logger);
            private:
                const std::string pathPrefix;
                
                std::shared_ptr<std::string> uri;
                web::Method method;
                std::shared_ptr<Adafruit_MCP23017> mcp;
                
                web::IWebSender* sender;
                sentinel::log::Logger& logger;
                
                int8_t getPinArgument();
                void blink(uint8_t pin);
                bool serveAllPins();
                bool servePin(uint8_t pin);
            };
        }
    }
}
#endif /* MOTORHANDLER_H */

