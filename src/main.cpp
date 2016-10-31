#ifndef UNIT_TEST
#include <Arduino.h>
#include "web/WebServer.h"
#include "conf/configuration.h"
#include "logger/logger.h"
#include "ota/ota.h"
#include "TestHandler.h"

OverTheAirUploadReceiver* otaReceiver = NULL;
Logger* logger;
WiFiServer* server;
WebServer* web;
TestHandler handler;

void setup() {
    logger = Logger::defaultLogger;
    logger->setLevel(DEBUG);
    logger->info("loading stage 1...");
    
    server = new WiFiServer(80);
    web = new WebServer(*server);
    web->registerHandler(handler);
    web->start();
}

void loop() {
    if (otaReceiver == NULL) {
        logger->info("loading stage 2...");
            otaReceiver = new OverTheAirUploadReceiver(*logger, 
                    WiFiConfiguration::SSID, WiFiConfiguration::Password);
            return;
    }

    if (otaReceiver->process())
        return;
    
    web->process();
    
    logger->info("YES");
    delay(500);
}
#endif