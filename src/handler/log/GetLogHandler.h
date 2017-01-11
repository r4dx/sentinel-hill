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

#ifndef GETLOGHANDLER_H
#define GETLOGHANDLER_H

#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <SD.h>
#include <string>

namespace sentinel {
    namespace handler {
        namespace log {
            class GetLogHandler : public web::IWebHandler {
            public:
                bool canHandle() const override;
                void setPath(web::Method method, std::string uri) override;
                void setSender(web::IWebSender& sender) override;
                bool handle() override;

                GetLogHandler(sentinel::log::Logger* logger);
                ~GetLogHandler() override {}
            private:
                std::string uri;
                web::Method method;                
                
                web::IWebSender* sender;
                sentinel::log::Logger* logger;
            };
        }
    }
}
#endif /* GETLOGHANDLER_H */

