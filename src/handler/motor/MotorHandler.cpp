#include "MotorHandler.h"
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

namespace sentinel {
    namespace handler {
        namespace motor {
            void MotorHandler::setPath(web::Method method, std::shared_ptr<std::string> uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool MotorHandler::canHandle() const {   
                return uri->compare("/motor") == 0 && method == web::Method::POST;
            }

            MotorHandler::MotorHandler(sentinel::log::Logger& logger) : 
                    logger(logger), 
                    sender(nullptr),
                    uri(std::shared_ptr<std::string>()),
                    method(web::Method::DELETE) { }

            void MotorHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            std::string to_string(int number) {
                char buff[256];
                itoa(number, buff, 10);
                return std::string(buff);
            }
            
            void testMCP() {
                Adafruit_MCP23017 mcp;
                Wire.begin(5, 4);
                mcp.begin();
                for (int pin = 0; pin < 16; pin++) {
                    mcp.pinMode(pin, OUTPUT);
                    //sender->sendContent(to_string(pin) + " ");
                    mcp.digitalWrite(pin, HIGH);
                    delay(1000);
                    mcp.digitalWrite(pin, LOW);
                }                
            }
            
            bool MotorHandler::handle() {
                Adafruit_MCP23017 mcp;
                Wire.begin(5, 4);
                mcp.begin();
                for (int pin = 0; pin < 16; pin++) {
                    mcp.pinMode(pin, OUTPUT);
                    sender->sendContent(to_string(pin) + " ");
                    mcp.digitalWrite(pin, HIGH);
                    delay(1000);
                    mcp.digitalWrite(pin, LOW);
                }
            }
        }
    }
}