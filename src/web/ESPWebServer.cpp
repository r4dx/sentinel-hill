#ifndef UNIT_TEST
#include "ESPWebServer.h"
#include <memory>

namespace sentinel {
    namespace web {
        ESPWebServer::ESPWebServer(ESP8266WebServer& server, log::Logger* logger) 
            : 
            server(server),
            wrapperList(),
            logger(logger)
            { }

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


        bool ESPWebServer::on(IWebHandler& handler) {
            if (this->started)
                return false;
            handler.setSender(*this);
            server.addHandler(wrap(handler));

            return true;
        }
        
        ESPWebServer::RequestHandlerWrapper* ESPWebServer::wrap(
            IWebHandler& handler) {
            auto result = new RequestHandlerWrapper(handler, logger);
            wrapperList.push_front(result);
            return result;
        }
        
        void ESPWebServer::send(int code, const std::string& content_type, 
                const std::string& content) {
            server.send(code, content_type.c_str(), content.c_str());
        }
        
        
        void ESPWebServer::sendContent(const std::string& content) {
            server.sendContent(content.c_str());
        }
        
        size_t ESPWebServer::streamFile(IWebFile& file, 
                const std::string& contentType) {
            
            return server.streamFile(file, contentType.c_str());
        };        

        ESPWebServer::RequestHandlerWrapper::RequestHandlerWrapper(
            IWebHandler& handler, log::Logger* logger) : 
            
            handler(handler), logger(logger) {};
        
        bool ESPWebServer::RequestHandlerWrapper::canHandle(HTTPMethod method, 
                String uri) {
            Method webMethod = httpMethodToMethod(method);            
            handler.setPath(webMethod, std::string(uri.c_str()));
            return handler.canHandle();
        }
        bool ESPWebServer::RequestHandlerWrapper::canUpload(String uri) {
            return false;
        }
        bool ESPWebServer::RequestHandlerWrapper::handle(
            ESP8266WebServer& server, HTTPMethod requestMethod, 
            String requestUri) {
            
            handler.setPath(httpMethodToMethod(requestMethod), 
                    std::string(requestUri.c_str()));
            return handler.handle();            
        }
        
    }
}

#endif