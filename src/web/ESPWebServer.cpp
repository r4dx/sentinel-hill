#ifndef UNIT_TEST
#include "ESPWebServer.h"
#include <memory>

namespace sentinel {
    namespace web {
        ESPWebServer::ESPWebServer(ESP8266WebServer& server) 
            : server(server),
            wrapperListEntry (nullptr) { }

        ESPWebServer::~ESPWebServer() {
            
            auto currentListEntry = wrapperListEntry;
            
            while (currentListEntry != nullptr) {
                auto next = currentListEntry->next;
                delete currentListEntry->wrapper;
                delete currentListEntry;
                currentListEntry = next;
            }
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


        bool ESPWebServer::on(IWebHandler& handler) {
            if (this->started)
                return false;
            handler.setSender(*this);
            
           
            
            server.addHandler(wrap(handler));

            return true;
        }
        
        ESPWebServer::RequestHandlerWrapper* ESPWebServer::wrap(
            IWebHandler& handler) {
            auto newEntry = new RequestHandlerWrapperListEntry();
            newEntry->wrapper = new RequestHandlerWrapper(handler);
            newEntry->next = wrapperListEntry;
            wrapperListEntry = newEntry;            
            return wrapperListEntry->wrapper;
        }
        
        HTTPMethod ESPWebServer::methodToHTTPMethod(Method method) {
            switch (method) {
                case Method::GET:
                    return HTTP_GET;
                case Method::POST:
                    return HTTP_POST;
                case Method::DELETE:
                    return HTTP_DELETE;
                default:
                    return HTTP_GET;
            }
        }
        
        Method ESPWebServer::httpMethodToMethod(HTTPMethod method) {
            switch (method) {
                HTTP_GET:
                    return Method::GET;
                HTTP_POST:
                    return Method::POST;
                HTTP_DELETE:
                    return Method::DELETE;
                default:
                    return Method::GET;
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
        
        bool ESPWebServer::RequestHandlerWrapper::canHandle(HTTPMethod method, 
                String uri) {
            handler.setPath(ESPWebServer::httpMethodToMethod(method), 
                    std::string(uri.c_str()));
            return handler.canHandle();
        }
        bool ESPWebServer::RequestHandlerWrapper::canUpload(String uri) {
            return false;
        }
        bool ESPWebServer::RequestHandlerWrapper::handle(
            ESP8266WebServer& server, HTTPMethod requestMethod, 
            String requestUri) {
            
            handler.setPath(ESPWebServer::httpMethodToMethod(requestMethod), 
                    std::string(requestUri.c_str()));
            return handler.handle();            
        }
        
    }
}

#endif