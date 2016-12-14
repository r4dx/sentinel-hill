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

#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <SD.h>

namespace sentinel {
    class TestHandler : public web::IWebHandler {
    public:
        std::string path() const override;
        web::Method method() const override;

        void setSender(web::IWebSender& sender) override;
        void process() override;
        
        TestHandler(Logger* logger);
        ~TestHandler() override {}
    private:
        std::string readFromFile(File* file);
        std::string getLogs();

        web::IWebSender* sender;
        Logger* logger;
        void sd_test();
    };
}
#endif /* TESTHANDLER_H */

