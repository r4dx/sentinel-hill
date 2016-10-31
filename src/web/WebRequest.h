#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <string>
#include "Method.h"

class WebRequest {
private:
    std::string request;
    
public:
    WebRequest(std::string request);

    std::string getRequest();    
    std::string getPath();
    Method getMethod();
};

#endif