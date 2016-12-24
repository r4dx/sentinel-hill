/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestHandler.h
 * Author: r4dx
 *
 * Created on 30 сентября 2016 г., 20:35
 */

#ifndef REMOVELOGHANDLER_H
#define REMOVELOGHANDLER_H

#include "web/IWebHandler.h"
#include "logger/ConsoleFileLoggerWrapper.h"
#include <SD.h>
#include <string>

namespace sentinel {
    namespace handler {
        namespace log {
            class RemoveLogHandler : public web::IWebHandler {
            public:
                std::string path() const override;
                web::Method method() const override;

                void setSender(web::IWebSender& sender) override;
                void process() override;

                RemoveLogHandler(sentinel::log::ConsoleFileLoggerWrapper& loggerWrapper);
                ~RemoveLogHandler() override {}
            private:
                web::IWebSender* sender;
                sentinel::log::ConsoleFileLoggerWrapper& loggerWrapper;
            };
        }
    }
}
#endif /* REMOVELOGHANDLER_H */

