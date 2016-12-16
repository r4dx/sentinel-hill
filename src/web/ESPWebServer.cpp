#ifndef UNIT_TEST
#include "ESPWebServer.h"

namespace sentinel {
    namespace web {
        ESPWebServer::ESPWebServer(ESP8266WebServer& server) 
            : server(server) {

        }

        ESPWebServer::~ESPWebServer() {
        }

        void ESPWebServer::start() {
            if (this->started)
                return;    
            server.begin();

            this->started = true;
        }

        void ESPWebServer::stop() {
            if (!this->started)
                return;   

            server.close();
            this->started = false;
        }

        void ESPWebServer::process() {
            if (!this->started)
                return;

            server.handleClient();
        }


        bool ESPWebServer::registerHandler(IWebHandler& handler) {
            if (this->started)
                return false;

            handler.setSender(*this);
            
            ESP8266WebServer::THandlerFunction handlerFunction = 
                    [&]{ handler.process(); };

            server.on(handler.path().c_str(), 
                    methodToHTTPMethod(handler.method()), handlerFunction);

            return true;
        }
        
        HTTPMethod ESPWebServer::methodToHTTPMethod(Method method) {
            switch (method) {
                case Method::GET:
                    return HTTP_GET;
                case Method::POST:
                    return HTTP_POST;
                    
                default:
                    return HTTP_GET;
            }
        }
        
        void ESPWebServer::send(int code, const std::string& content_type, 
                const std::string& content) {
            server.send(code, content_type.c_str(), content.c_str());
        }
        
        size_t ESPWebServer::streamFile(IWebFile& file, 
                const std::string& contentType) {
            
            return server.streamFile(file, contentType.c_str());
        };        
    }
}

#endif