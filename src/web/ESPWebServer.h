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
        // N.B. calling handler canHandle() + handle() are not thread safe 
        // in this implementation (there are no threads in ESP8266)
        
        class ESPWebServer : public IWebServer, IWebSender {
        public:
            ESPWebServer(ESP8266WebServer& server, log::Logger& logger);

            bool on(IWebHandler& handler) override;
            void start() override;
            void process() override;
            void stop() override;
            
            void send(int code, const std::string& content_type, 
                const std::string& content) override;
            
            void sendContent(const std::string& content) override;

            size_t streamFile(IWebFile& file, 
                const std::string& contentType) override;
            
        private:                     
            ESP8266WebServer& server;
            bool started = false;
            log::Logger& logger;
            
            
            class RequestHandlerWrapper : public RequestHandler {
            public:
                RequestHandlerWrapper(IWebHandler& handler, log::Logger& logger);
                
                bool canHandle(HTTPMethod method, String uri) override;
                bool canUpload(String uri) override;
                bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, 
                    String requestUri) override;
                
            private:
                IWebHandler& handler;
                log::Logger& logger;
            };

            collections::ptr_list<RequestHandlerWrapper> wrapperList;
            RequestHandlerWrapper* wrap(IWebHandler& handler);
        };
    }
}
#endif
#endif