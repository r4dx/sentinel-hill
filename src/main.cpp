#ifndef UNIT_TEST
//#include <vector> // hack to make it compile - https://github.com/esp8266/Arduino/issues/2549
#include <WiFiClient.h>
#include <Arduino.h>
#include "web/ESPWebServer.h"
#include "conf/configuration.h"
#include "logger/logger.h"
#include "ota/ota.h"
#include "logger/ConsoleFileLoggerWrapper.h"
#include "handler/log/GetLogHandler.h"
#include "handler/log/RemoveLogHandler.h"
#include "handler/sd/BrowseSDHandler.h"
#include "time/TimeString.h"

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::ConsoleFileLoggerWrapper* loggerWrapper;
sentinel::web::IWebServer* web;

void initLogger() {
    loggerWrapper = new sentinel::log::ConsoleFileLoggerWrapper(
            sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName,
            *(new sentinel::time::MillisTimeProvider()));
    
    auto logger = loggerWrapper->get();
    logger->setLevel(sentinel::log::DEBUG);    
}

void initWebServer() {
    auto logger = loggerWrapper->get();
    logger->info("Loading handlers");
    
    // Will be never deleted!
    auto getLogHandler = new sentinel::handler::log::GetLogHandler(logger);
    auto removeLogHandler = new sentinel::handler::log::RemoveLogHandler(*loggerWrapper);
    auto browseSDHandler = new sentinel::handler::sd::BrowseSDHandler(logger);

    ESP8266WebServer* server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server, logger);

    web->on(*getLogHandler);
    web->on(*removeLogHandler);
    web->on(*browseSDHandler);
    logger->info("Starting web server");
    web->start();    
    logger->info("Started successfully");
}

void setup() {
    initLogger();
    initWebServer();
}

void loop() {
    auto logger = loggerWrapper->get();
    
    if (otaReceiver == nullptr) {
        logger->info("Initializing Over-the-air update receiver");
            otaReceiver = new sentinel::ota::OverTheAirUploadReceiver(*logger, 
                    configuration::wifi::SSID, configuration::wifi::Password);
            logger->info("Initialized");
            return;
    }

    if (otaReceiver->process())
        return;

    web->process();

    //logger->info("Ping");
    delay(100);
}
#endif