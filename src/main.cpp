#ifndef UNIT_TEST
#include <Arduino.h>
#include "web/ESPWebServer.h"
#include "conf/configuration.h"
#include "logger/logger.h"
#include "ota/ota.h"
#include "handler/log/GetLogHandler.h"
#include "logger/ConsoleFileLoggerWrapper.h"
#include "handler/log/RemoveLogHandler.h"

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::ConsoleFileLoggerWrapper* loggerWrapper;
ESP8266WebServer* server;
sentinel::web::IWebServer* web;

void setup() {
    loggerWrapper = new sentinel::log::ConsoleFileLoggerWrapper(
            sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName,
            *(new MillisTimeProvider()));
    
    auto logger = loggerWrapper->get();
    
    logger->setLevel(sentinel::log::DEBUG);
    logger->info("loading stage 1...");

    auto getLogHandler = new sentinel::handler::log::GetLogHandler(logger);
    auto removeLogHandler = new sentinel::handler::log::RemoveLogHandler(*loggerWrapper);

    server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server);

    web->registerHandler(*getLogHandler);
    web->registerHandler(*removeLogHandler);
    web->start();
}

void loop() {
    auto logger = loggerWrapper->get();
    
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
    delay(5000);
}
#endif