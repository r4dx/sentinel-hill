#include "IOExpanderHandler.h"
#include <SPI.h>
#include <Wire.h>

namespace sentinel {
    namespace handler {
        namespace motor {
            void IOExpanderHandler::setPath(web::Method method, std::shared_ptr<std::string> uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool IOExpanderHandler::canHandle() const {   
                return uri->compare(0, pathPrefix.size(), pathPrefix) == 0 && 
                        method == web::Method::POST;
            }

            IOExpanderHandler::IOExpanderHandler(sentinel::log::Logger& logger) : 
                    logger(logger), 
                    sender(nullptr),
                    uri(std::shared_ptr<std::string>()),
                    method(web::Method::DELETE),
                    pathPrefix("/gpio-expander") { }

            void IOExpanderHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            std::string to_string(int number) {
                char buff[256];
                itoa(number, buff, 10);
                return std::string(buff);
            }
            
            uint8_t to_uint8_t(std::string str) {
                // can't distinguish 0 from error in atoi result
                if (str == "0")
                    return 0;
                
                int result = atoi(str.c_str());
                if (result > 255 || result == 0)
                    return -1;
                
                return result;
            }            
            
            int8_t IOExpanderHandler::getPinArgument() {
                if (uri->size() <= pathPrefix.size() + 1)
                    return -1;
                
                std::string argument = uri->substr(pathPrefix.size() + 1);
                uint8_t result = to_uint8_t(argument);
                return result;
            }
            
            void IOExpanderHandler::blink(uint8_t pin) {
                mcp->pinMode(pin, OUTPUT);
                sender->sendContent(to_string(pin));
                mcp->digitalWrite(pin, HIGH);
                delay(1000);
                mcp->digitalWrite(pin, LOW);                
                sender->sendContent(" ");
            }
            
            bool IOExpanderHandler::serveAllPins() {
                sender->send(200, "text/html", "OK");
                for (int pin = 0; pin < 16; pin++)
                    blink(pin);

                return true;                
            }
            
            bool IOExpanderHandler::servePin(uint8_t pin) {
                if (pin > 15) {
                    sender->send(404, "text/html", "Pin's not found");
                    return false;
                }
                
                sender->send(200, "text/html", "OK");
                blink(pin);
                return true;                
            }

            
            bool IOExpanderHandler::handle() {
                mcp.reset(new Adafruit_MCP23017());
                Wire.begin(5, 4);
                mcp->begin();
                int8_t pin = getPinArgument();
                if (pin > -1)
                    return servePin(pin);

                return serveAllPins();
            }
        }
    }
}