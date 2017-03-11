#include "MotorHandler.h"
#include <SPI.h>

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

            bool MotorHandler::handle() {
                
            }
        }
    }
}