#ifndef UNIT_TEST
#include <Arduino.h>
#include "web/ESPWebServer.h"
#include "conf/configuration.h"
#include "logger/logger.h"
#include "ota/ota.h"
#include "handler/log/GetLogHandler.h"
#include "logger/LoggerFactory.h"

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::Logger* logger;
ESP8266WebServer* server;
sentinel::web::IWebServer* web;

void setup() {
    
    logger = sentinel::log::LoggerFactory::createDefaultLogger();
    logger->setLevel(sentinel::log::DEBUG);
    logger->info("loading stage 1...");

    sentinel::handler::log::GetLogHandler* handler = 
            new sentinel::handler::log::GetLogHandler(logger);

    server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server);

    web->registerHandler(*handler);
    web->start();
}

void loop() {
    if (otaReceiver == nullptr) {
        logger->info("loading stage 2...");
            otaReceiver = new sentinel::ota::OverTheAirUploadReceiver(*logger, 
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