#ifndef UNIT_TEST
#ifndef ESPWEBSERVER_H
#define ESPWEBSERVER_H

#include <ESP8266WebServer.h>
#include <map>
#include <memory>
#include "IWebHandler.h"
#include "logger/logger.h"
#include "IWebServer.h"
#include "collections/ptr_list.h"

namespace sentinel {
    namespace web {
        class ESPWebServer : public IWebServer, IWebSender {
        public:
            ESPWebServer(ESP8266WebServer& server);
            ~ESPWebServer();

            bool on(IWebHandler& handler) override;
            void start() override;
            void process() override;
            void stop() override;
            
            void send(int code, const std::string& content_type, 
                const std::string& content) override;

            size_t streamFile(IWebFile& file, 
                const std::string& contentType) override;
            
        private:           
            static HTTPMethod methodToHTTPMethod(Method method);
            static Method httpMethodToMethod(HTTPMethod method);
            
            ESP8266WebServer& server;
            bool started = false;
           
            
            class RequestHandlerWrapper : public RequestHandler {
            public:
                RequestHandlerWrapper(IWebHandler& handler) : handler(handler) {}
                
                bool canHandle(HTTPMethod method, String uri) override;
                bool canUpload(String uri) override;
                bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, 
                    String requestUri) override;
                
            private:
                IWebHandler& handler;
            };

            collections::ptr_list<RequestHandlerWrapper> wrapperList;
            RequestHandlerWrapper* wrap(IWebHandler& handler);
        };
    }
}
#endif
#endif