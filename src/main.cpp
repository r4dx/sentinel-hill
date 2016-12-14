#ifndef UNIT_TEST
#include <Arduino.h>
#include "web/ESPWebServer.h"
#include "conf/configuration.h"
#include "logger/logger.h"
#include "ota/ota.h"
#include "TestHandler.h"

OverTheAirUploadReceiver* otaReceiver = nullptr;
Logger* logger;
ESP8266WebServer* server;
sentinel::web::IWebServer* web;

void setup() {
    logger = Logger::getDefaultLogger();
    logger->setLevel(DEBUG);
    logger->info("loading stage 1...");

    sentinel::TestHandler* handler = new sentinel::TestHandler(logger);

    server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server);

    web->registerHandler(*handler);
    web->start();
}

void loop() {
    if (otaReceiver == nullptr) {
        logger->info("loading stage 2...");
            otaReceiver = new OverTheAirUploadReceiver(*logger, 
                    configuration::wifi::SSID, configuration::wifi::Password);
            return;
    }

    if (otaReceiver->process())
        return;

    web->process();

    logger->info("YES");
    delay(1000);
}
#endif