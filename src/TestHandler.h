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

#include "web/WebRequest.h"
#include "web/WebResponse.h"
#include "web/IWebHandler.h"
#include "logger/logger.h"
#include <SD.h>

class TestHandler : public IWebHandler {
public:
    WebResponse get(WebRequest& request);
    WebResponse post(WebRequest& request);
    std::string getPath() const;
    TestHandler(Logger* logger);
private:
    std::string readFromFile(File* file);
    std::string getLogs();
    
    Logger* logger;
    void sd_test();
};

#endif /* TESTHANDLER_H */

