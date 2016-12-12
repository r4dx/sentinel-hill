#ifndef UNIT_TEST
#include "WebServer.h"

WebResponse const WebResponse::invalid = WebResponse("Invalid");

WebServer::WebServer(WiFiServer& server) : server(server) {
    this->handlers = std::map<std::string, IWebHandler*>();
    this->logger = Logger::getDefaultLogger();
}
       
WebServer::~WebServer() {
}

void WebServer::start() {
    if (this->started)
        return;    
    server.begin();
    
    this->started = true;
}

void WebServer::stop() {
    if (!this->started)
        return;   
    
    server.close();
    this->started = false;
}

void WebServer::process() {
    if (!this->started)
        return;
    
    WiFiClient client = this->server.available();
    if (!client)
        return;
    
    logger->debug("Got client");
    
    String requestString = client.readStringUntil('\r');
    client.flush();
    
    logger->debug("Read string");
    
    WebRequest request(std::string(requestString.c_str()));
    logger->debug("Built request");
    WebResponse response = handleRequest(request);
    logger->debug("Got response");
    client.print(response.getResponse().c_str());
    logger->debug("Printed response");
}

WebResponse WebServer::handleRequest(WebRequest request) {
    logger->debug(("Processing " + request.getPath()));  
    
    if (this->handlers.count(request.getPath()) != 1)
        return WebResponse("Invalid: " + this->getAllHandlersString());
    
    logger->debug("Getting a handler");
    IWebHandler* handler = this->handlers[request.getPath()];
    if (handler == nullptr) {
        logger->debug("handler is NULL for some reason!!!");
        return WebResponse::invalid;
    }
            
    logger->debug("Getting method");
    Method method = request.getMethod();   
    switch (method) {
        case GET:
            logger->debug("It's GET!");
            return handler->get(request);
        case POST:
            logger->debug("It's POST!");
            return handler->post(request);
        default:
            logger->debug("INVALID!");
            return WebResponse::invalid;
    }
}

std::string WebServer::getAllHandlersString() {
    std::string result = "";
    
    typedef std::map<std::string, IWebHandler*>::iterator it_type;
    
    for (auto& iterator : this->handlers) {
        result += iterator.first + " - " + (iterator.second == nullptr ? 
            "NULL" : "OKAY");
    }
    
    return result;
}

bool WebServer::registerHandler(const IWebHandler& handler) {
    if (this->started)
        return false;
       
    logger->debug("Checking if there's already a handler");
    
    if (this->handlers.count(handler.getPath()) != 0)
        return false;
    
    logger->debug("Adding handler " + handler.getPath());
    this->handlers[handler.getPath()] = &(const_cast<IWebHandler&>(handler));
    logger->debug("All handlers are: " + this->getAllHandlersString());
    
    return true;
}
#endif