#ifndef UNIT_TEST
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <map>
#include <memory>
#include "WebRequest.h"
#include "WebResponse.h"
#include "IWebHandler.h"
#include "logger/logger.h"

class WebServer {
public:
    WebServer(WiFiServer& server);
    ~WebServer();
    
    bool registerHandler(const IWebHandler& handler);
    void start();
    void process();
    void stop();
    
private:
    Logger* logger;
    WiFiServer& server;
    bool started = false;
        
    // Should be unordered_map but platformio won't compile with it
    std::map<std::string, IWebHandler*> handlers;
    WebResponse handleRequest(WebRequest request);
    std::string getAllHandlersString();
};

#endif
#endif