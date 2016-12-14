#ifndef UNIT_TEST
#ifndef ESPWEBSERVER_H
#define ESPWEBSERVER_H

#include <ESP8266WebServer.h>
#include <map>
#include <memory>
#include "IWebHandler.h"
#include "logger/logger.h"
#include "IWebServer.h"

namespace sentinel {
    namespace web {
        class ESPWebServer : public IWebServer, IWebSender {
        public:
            ESPWebServer(ESP8266WebServer& server);
            ~ESPWebServer();

            bool registerHandler(IWebHandler& handler) override;
            void start() override;
            void process() override;
            void stop() override;
            
            void send(int code, const std::string& content_type, 
                const std::string& content) override;

        private:
            HTTPMethod methodToHTTPMethod(Method method);
            
            ESP8266WebServer& server;
            bool started = false;
        };
    }
}
#endif
#endif